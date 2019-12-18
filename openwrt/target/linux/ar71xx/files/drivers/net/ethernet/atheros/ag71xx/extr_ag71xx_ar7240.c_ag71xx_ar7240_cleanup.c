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
struct ar7240sw {int /*<<< orphan*/  swdev; } ;
struct ag71xx {struct ar7240sw* phy_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ar7240sw*) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

void ag71xx_ar7240_cleanup(struct ag71xx *ag)
{
	struct ar7240sw *as = ag->phy_priv;

	if (!as)
		return;

	unregister_switch(&as->swdev);
	kfree(as);
	ag->phy_priv = NULL;
}