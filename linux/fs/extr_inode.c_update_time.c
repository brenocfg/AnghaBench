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
struct timespec64 {int dummy; } ;
struct inode {TYPE_1__* i_op; } ;
struct TYPE_2__ {int (* update_time ) (struct inode*,struct timespec64*,int) ;} ;

/* Variables and functions */
 int generic_update_time (struct inode*,struct timespec64*,int) ; 

__attribute__((used)) static int update_time(struct inode *inode, struct timespec64 *time, int flags)
{
	int (*update_time)(struct inode *, struct timespec64 *, int);

	update_time = inode->i_op->update_time ? inode->i_op->update_time :
		generic_update_time;

	return update_time(inode, time, flags);
}