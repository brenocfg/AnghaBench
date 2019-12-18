#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ping_auto_globals_mask; } ;

/* Variables and functions */
 TYPE_1__* ZCSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preload_script ; 
 int /*<<< orphan*/  zend_accel_set_auto_globals (scalar_t__) ; 

__attribute__((used)) static void preload_activate(void)
{
	if (ZCSG(preload_script)->ping_auto_globals_mask) {
		zend_accel_set_auto_globals(ZCSG(preload_script)->ping_auto_globals_mask);
	}
}