#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kernfs_open_node {int /*<<< orphan*/  event; int /*<<< orphan*/  poll; } ;
struct kernfs_open_file {scalar_t__ event; } ;
struct TYPE_4__ {struct kernfs_open_node* open; } ;
struct kernfs_node {TYPE_2__ attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int DEFAULT_POLLMASK ; 
 int EPOLLERR ; 
 int EPOLLPRI ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct kernfs_node* kernfs_dentry_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_get_active (struct kernfs_node*) ; 
 struct kernfs_open_file* kernfs_of (struct file*) ; 
 int /*<<< orphan*/  kernfs_put_active (struct kernfs_node*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t kernfs_fop_poll(struct file *filp, poll_table *wait)
{
	struct kernfs_open_file *of = kernfs_of(filp);
	struct kernfs_node *kn = kernfs_dentry_node(filp->f_path.dentry);
	struct kernfs_open_node *on = kn->attr.open;

	if (!kernfs_get_active(kn))
		goto trigger;

	poll_wait(filp, &on->poll, wait);

	kernfs_put_active(kn);

	if (of->event != atomic_read(&on->event))
		goto trigger;

	return DEFAULT_POLLMASK;

 trigger:
	return DEFAULT_POLLMASK|EPOLLERR|EPOLLPRI;
}