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
struct vfsmount {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_expire; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 TYPE_1__* real_mount (struct vfsmount*) ; 

void mnt_set_expiry(struct vfsmount *mnt, struct list_head *expiry_list)
{
	namespace_lock();

	list_add_tail(&real_mount(mnt)->mnt_expire, expiry_list);

	namespace_unlock();
}