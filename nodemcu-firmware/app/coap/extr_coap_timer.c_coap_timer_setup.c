#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  os_timer_func_t ;
typedef  int /*<<< orphan*/  coap_tick_t ;
typedef  int /*<<< orphan*/  coap_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWTIMER_REG_CB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 int /*<<< orphan*/  coap_timer ; 
 scalar_t__ coap_timer_tick ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

void coap_timer_setup(coap_queue_t ** queue, coap_tick_t t){
  os_timer_disarm(&coap_timer);
  os_timer_setfn(&coap_timer, (os_timer_func_t *)coap_timer_tick, queue);
  SWTIMER_REG_CB(coap_timer_tick, SWTIMER_RESUME);
    //coap_timer_tick processes a queue, my guess is that it is ok to resume the timer from where it left off
  os_timer_arm(&coap_timer, t, 0);   // no repeat
}