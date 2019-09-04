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
struct TYPE_3__ {int speed_lim_off; int speed_lim_off_timeout; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int UI_FREQ ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  read_db_value (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 
 int strtod (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_speed_lim_off(UIState *s) {
  char *speed_lim_off = NULL;
  read_db_value(NULL, "SpeedLimitOffset", &speed_lim_off, NULL);
  s->speed_lim_off = 0.;
  if (speed_lim_off) {
    s->speed_lim_off = strtod(speed_lim_off, NULL);
    free(speed_lim_off);
  }
  s->speed_lim_off_timeout = 2 * UI_FREQ; // 0.5Hz
}