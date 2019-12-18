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
struct gsw_mt753x {int /*<<< orphan*/  swdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

void mt753x_swconfig_destroy(struct gsw_mt753x *gsw)
{
	unregister_switch(&gsw->swdev);
}