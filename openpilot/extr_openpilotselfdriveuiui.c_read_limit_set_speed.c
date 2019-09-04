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
struct TYPE_3__ {int limit_set_speed; int limit_set_speed_timeout; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int UI_FREQ ; 
 int /*<<< orphan*/  free (char*) ; 
 int read_db_value (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_limit_set_speed(UIState *s) {
  char *limit_set_speed;
  const int result = read_db_value(NULL, "LimitSetSpeed", &limit_set_speed, NULL);
  if (result == 0) {
    s->limit_set_speed = limit_set_speed[0] == '1';
    free(limit_set_speed);
  }
  s->limit_set_speed_timeout =  2 * UI_FREQ; // 0.2Hz
}