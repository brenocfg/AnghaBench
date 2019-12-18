#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int h; } ;

/* Variables and functions */
#define  add_fade 129 
 scalar_t__ boot ; 
 scalar_t__ fade_interval ; 
 int fade_state ; 
 scalar_t__ flash_state ; 
 scalar_t__ no_flash ; 
 int /*<<< orphan*/  set_color (TYPE_1__,int) ; 
 scalar_t__ state ; 
#define  sub_fade 128 
 scalar_t__ timer_elapsed (scalar_t__) ; 
 scalar_t__ timer_read () ; 
 TYPE_1__ underglow ; 

void fade_rgb (void) {
  static uint16_t fade_timer;
  if (state == boot) {return;}
  if (!fade_timer) {fade_timer = timer_read();}
  if (timer_elapsed(fade_timer) < fade_interval) {return;}
  switch (fade_state) {
  case add_fade:
    if (underglow.h == 359) {
      fade_state = sub_fade;
      return;
    }
    underglow.h = underglow.h + 1;
    break;

  case sub_fade:
    if (underglow.h == 0) {
      fade_state = add_fade;
      return;
    }
    underglow.h = underglow.h - 1;
    break;
  }
  fade_timer = timer_read();
  if (flash_state == no_flash) {
    set_color(underglow, false);
  }
}