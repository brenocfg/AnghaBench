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
struct TYPE_3__ {int volume_timeout; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int UI_FREQ ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int system (char*) ; 

__attribute__((used)) static void set_volume(UIState *s, int volume) {
  char volume_change_cmd[64];
  sprintf(volume_change_cmd, "service call audio 3 i32 3 i32 %d i32 1", volume);

  // 5 second timeout at 60fps
  s->volume_timeout = 5 * UI_FREQ;
  int volume_changed = system(volume_change_cmd);
}