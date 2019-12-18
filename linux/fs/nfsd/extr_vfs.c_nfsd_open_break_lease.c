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
struct inode {int dummy; } ;

/* Variables and functions */
 int NFSD_MAY_NOT_BREAK_LEASE ; 
 int NFSD_MAY_WRITE ; 
 unsigned int O_NONBLOCK ; 
 unsigned int O_RDONLY ; 
 unsigned int O_WRONLY ; 
 int break_lease (struct inode*,unsigned int) ; 

int nfsd_open_break_lease(struct inode *inode, int access)
{
	unsigned int mode;

	if (access & NFSD_MAY_NOT_BREAK_LEASE)
		return 0;
	mode = (access & NFSD_MAY_WRITE) ? O_WRONLY : O_RDONLY;
	return break_lease(inode, mode | O_NONBLOCK);
}