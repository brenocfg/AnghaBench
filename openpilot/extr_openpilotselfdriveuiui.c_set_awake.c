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
struct TYPE_4__ {int awake_timeout; int awake; int /*<<< orphan*/  fb; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int /*<<< orphan*/  HWC_POWER_MODE_NORMAL ; 
 int /*<<< orphan*/  HWC_POWER_MODE_OFF ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  framebuffer_set_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_brightness (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_awake(UIState *s, bool awake) {
  if (awake) {
    // 30 second timeout at 30 fps
    s->awake_timeout = 30*30;
  }
  if (s->awake != awake) {
    s->awake = awake;

    if (awake) {
      LOG("awake normal");
      framebuffer_set_power(s->fb, HWC_POWER_MODE_NORMAL);
    } else {
      LOG("awake off");
      set_brightness(s, 0);
      framebuffer_set_power(s->fb, HWC_POWER_MODE_OFF);
    }
  }
}