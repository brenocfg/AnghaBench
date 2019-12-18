#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint ;
struct TYPE_11__ {TYPE_1__* Instance; } ;
struct TYPE_9__ {TYPE_5__ tim; TYPE_3__* channel; int /*<<< orphan*/  callback; } ;
typedef  TYPE_2__ pyb_timer_obj_t ;
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/  channel; int /*<<< orphan*/  callback; } ;
typedef  TYPE_3__ pyb_timer_channel_obj_t ;
struct TYPE_8__ {int DIER; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICROPY_ERROR_PRINTER ; 
 TYPE_2__** MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int PYB_TIMER_OBJ_ALL_NUM ; 
 int TIMER_IRQ_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HAL_TIM_CLEAR_IT (TYPE_5__*,int) ; 
 int /*<<< orphan*/  __HAL_TIM_DISABLE_IT (TYPE_5__*,int) ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  pyb_timer_obj_all ; 
 int /*<<< orphan*/  timer_handle_irq_channel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void timer_irq_handler(uint tim_id) {
    if (tim_id - 1 < PYB_TIMER_OBJ_ALL_NUM) {
        // get the timer object
        pyb_timer_obj_t *tim = MP_STATE_PORT(pyb_timer_obj_all)[tim_id - 1];

        if (tim == NULL) {
            // Timer object has not been set, so we can't do anything.
            // This can happen under normal circumstances for timers like
            // 1 & 10 which use the same IRQ.
            return;
        }

        // Check for timer (versus timer channel) interrupt.
        timer_handle_irq_channel(tim, 0, tim->callback);
        uint32_t handled = TIMER_IRQ_MASK(0);

        // Check to see if a timer channel interrupt was pending
        pyb_timer_channel_obj_t *chan = tim->channel;
        while (chan != NULL) {
            timer_handle_irq_channel(tim, chan->channel, chan->callback);
            handled |= TIMER_IRQ_MASK(chan->channel);
            chan = chan->next;
        }

        // Finally, clear any remaining interrupt sources. Otherwise we'll
        // just get called continuously.
        uint32_t unhandled = tim->tim.Instance->DIER & 0xff & ~handled;
        if (unhandled != 0) {
            __HAL_TIM_DISABLE_IT(&tim->tim, unhandled);
            __HAL_TIM_CLEAR_IT(&tim->tim, unhandled);
            mp_printf(MICROPY_ERROR_PRINTER, "unhandled interrupt SR=0x%02x (now disabled)\n", (unsigned int)unhandled);
        }
    }
}