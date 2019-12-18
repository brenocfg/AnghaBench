#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* i_itemp; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_5__ {int /*<<< orphan*/  li_lv_shadow; } ;
struct TYPE_7__ {TYPE_1__ ili_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_ili_zone ; 

void
xfs_inode_item_destroy(
	xfs_inode_t	*ip)
{
	kmem_free(ip->i_itemp->ili_item.li_lv_shadow);
	kmem_zone_free(xfs_ili_zone, ip->i_itemp);
}