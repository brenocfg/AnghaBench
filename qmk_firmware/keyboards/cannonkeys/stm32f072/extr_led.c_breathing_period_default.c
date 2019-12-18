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

/* Variables and functions */
 int /*<<< orphan*/  BREATHING_PERIOD ; 
 int /*<<< orphan*/  breathing_period_set (int /*<<< orphan*/ ) ; 

void breathing_period_default(void) {
  breathing_period_set(BREATHING_PERIOD);
}