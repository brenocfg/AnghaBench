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
struct ar7240sw {int /*<<< orphan*/  stats_lock; } ;
struct ag71xx {int /*<<< orphan*/  link_work; struct ar7240sw* phy_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ar7240sw* ar7240_probe (struct ag71xx*) ; 
 int /*<<< orphan*/  ar7240sw_reset (struct ar7240sw*) ; 
 int /*<<< orphan*/  link_function ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

int ag71xx_ar7240_init(struct ag71xx *ag)
{
	struct ar7240sw *as;

	as = ar7240_probe(ag);
	if (!as)
		return -ENODEV;

	ag->phy_priv = as;
	ar7240sw_reset(as);

	rwlock_init(&as->stats_lock);
	INIT_DELAYED_WORK(&ag->link_work, link_function);

	return 0;
}