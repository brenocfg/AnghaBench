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
struct zd_mac {int /*<<< orphan*/  lock; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 int /*<<< orphan*/  ZD_MEMCLEAR (struct zd_mac*,int) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_workqueue ; 

void zd_mac_clear(struct zd_mac *mac)
{
	flush_workqueue(zd_workqueue);
	zd_chip_clear(&mac->chip);
	ZD_ASSERT(!spin_is_locked(&mac->lock));
	ZD_MEMCLEAR(mac, sizeof(struct zd_mac));
}