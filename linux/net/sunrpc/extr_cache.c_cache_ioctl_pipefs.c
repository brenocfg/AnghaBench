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
struct file {int dummy; } ;
struct cache_detail {int dummy; } ;
struct TYPE_2__ {struct cache_detail* private; } ;

/* Variables and functions */
 TYPE_1__* RPC_I (struct inode*) ; 
 long cache_ioctl (struct inode*,struct file*,unsigned int,unsigned long,struct cache_detail*) ; 
 struct inode* file_inode (struct file*) ; 

__attribute__((used)) static long cache_ioctl_pipefs(struct file *filp,
			      unsigned int cmd, unsigned long arg)
{
	struct inode *inode = file_inode(filp);
	struct cache_detail *cd = RPC_I(inode)->private;

	return cache_ioctl(inode, filp, cmd, arg, cd);
}