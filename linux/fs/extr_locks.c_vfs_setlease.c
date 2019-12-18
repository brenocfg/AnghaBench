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
struct file_lock {int dummy; } ;
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {int (* setlease ) (struct file*,long,struct file_lock**,void**) ;} ;

/* Variables and functions */
 int generic_setlease (struct file*,long,struct file_lock**,void**) ; 
 int /*<<< orphan*/  setlease_notifier (long,struct file_lock*) ; 
 int stub1 (struct file*,long,struct file_lock**,void**) ; 

int
vfs_setlease(struct file *filp, long arg, struct file_lock **lease, void **priv)
{
	if (lease)
		setlease_notifier(arg, *lease);
	if (filp->f_op->setlease)
		return filp->f_op->setlease(filp, arg, lease, priv);
	else
		return generic_setlease(filp, arg, lease, priv);
}