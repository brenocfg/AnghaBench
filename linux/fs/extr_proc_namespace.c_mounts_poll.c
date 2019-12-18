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
struct seq_file {int poll_event; struct proc_mounts* private; } ;
struct proc_mounts {struct mnt_namespace* ns; } ;
struct mnt_namespace {int /*<<< orphan*/  event; int /*<<< orphan*/  poll; } ;
struct file {struct seq_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t mounts_poll(struct file *file, poll_table *wait)
{
	struct seq_file *m = file->private_data;
	struct proc_mounts *p = m->private;
	struct mnt_namespace *ns = p->ns;
	__poll_t res = EPOLLIN | EPOLLRDNORM;
	int event;

	poll_wait(file, &p->ns->poll, wait);

	event = READ_ONCE(ns->event);
	if (m->poll_event != event) {
		m->poll_event = event;
		res |= EPOLLERR | EPOLLPRI;
	}

	return res;
}