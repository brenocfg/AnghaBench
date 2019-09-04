#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ last_event_time; int timer_running; scalar_t__ longpress_delay_us; int lastpos; scalar_t__ click_delay_us; int /*<<< orphan*/  timer; scalar_t__ last_recent_event_was_release; scalar_t__ last_recent_event_was_press; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ROTARY_CLICK_INDEX ; 
 int /*<<< orphan*/  ROTARY_LONGPRESS_INDEX ; 
 int /*<<< orphan*/  callback_call (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  lua_getstate () ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lrotary_check_timer(DATA *d, uint32_t time_us, bool dotimer)
{
  uint32_t delay = time_us - d->last_event_time;
  if (d->timer_running) {
    os_timer_disarm(&d->timer);
    d->timer_running = 0;
  }

  int timeout = -1;

  if (d->last_recent_event_was_press) {
    if (delay > d->longpress_delay_us) {
      callback_call(lua_getstate(), d, ROTARY_LONGPRESS_INDEX, (d->lastpos << 1) >> 1, d->last_event_time + d->longpress_delay_us);
      d->last_recent_event_was_press = 0;
    } else {
      timeout = (d->longpress_delay_us - delay) / 1000;
    }
  }
  if (d->last_recent_event_was_release) {
    if (delay > d->click_delay_us) {
      callback_call(lua_getstate(), d, ROTARY_CLICK_INDEX, (d->lastpos << 1) >> 1, d->last_event_time + d->click_delay_us);
      d->last_recent_event_was_release = 0;
    } else {
      timeout = (d->click_delay_us - delay) / 1000;
    }
  }

  if (dotimer && timeout >= 0) {
    d->timer_running = 1;
    os_timer_arm(&d->timer, timeout + 1, 0);
  }
}