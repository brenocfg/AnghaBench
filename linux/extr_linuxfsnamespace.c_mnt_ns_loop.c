#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mnt_namespace {scalar_t__ seq; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_6__ {TYPE_2__* nsproxy; } ;
struct TYPE_5__ {TYPE_1__* mnt_ns; } ;
struct TYPE_4__ {scalar_t__ seq; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  get_proc_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_mnt_ns_file (struct dentry*) ; 
 struct mnt_namespace* to_mnt_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mnt_ns_loop(struct dentry *dentry)
{
	/* Could bind mounting the mount namespace inode cause a
	 * mount namespace loop?
	 */
	struct mnt_namespace *mnt_ns;
	if (!is_mnt_ns_file(dentry))
		return false;

	mnt_ns = to_mnt_ns(get_proc_ns(dentry->d_inode));
	return current->nsproxy->mnt_ns->seq >= mnt_ns->seq;
}