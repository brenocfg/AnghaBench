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
struct kernfs_open_node {int /*<<< orphan*/  event; int /*<<< orphan*/  poll; } ;
struct kernfs_open_file {scalar_t__ event; TYPE_3__* file; } ;
struct TYPE_5__ {struct kernfs_open_node* open; } ;
struct kernfs_node {TYPE_2__ attr; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_6__ {TYPE_1__ f_path; } ;

/* Variables and functions */
 int DEFAULT_POLLMASK ; 
 int EPOLLERR ; 
 int EPOLLPRI ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct kernfs_node* kernfs_dentry_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__poll_t kernfs_generic_poll(struct kernfs_open_file *of, poll_table *wait)
{
	struct kernfs_node *kn = kernfs_dentry_node(of->file->f_path.dentry);
	struct kernfs_open_node *on = kn->attr.open;

	poll_wait(of->file, &on->poll, wait);

	if (of->event != atomic_read(&on->event))
		return DEFAULT_POLLMASK|EPOLLERR|EPOLLPRI;

	return DEFAULT_POLLMASK;
}