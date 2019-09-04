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
struct vm_area_struct {int dummy; } ;
struct socket {TYPE_1__* ops; } ;
struct file {struct socket* private_data; } ;
struct TYPE_2__ {int (* mmap ) (struct file*,struct socket*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int stub1 (struct file*,struct socket*,struct vm_area_struct*) ; 

__attribute__((used)) static int sock_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct socket *sock = file->private_data;

	return sock->ops->mmap(file, sock, vma);
}