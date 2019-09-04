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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  extents_lock; } ;

/* Variables and functions */
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 int hfsplus_ext_write_extent_locked (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hfsplus_ext_write_extent(struct inode *inode)
{
	int res;

	mutex_lock(&HFSPLUS_I(inode)->extents_lock);
	res = hfsplus_ext_write_extent_locked(inode);
	mutex_unlock(&HFSPLUS_I(inode)->extents_lock);

	return res;
}