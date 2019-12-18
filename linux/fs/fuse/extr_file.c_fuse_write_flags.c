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
struct kiocb {int ki_flags; TYPE_1__* ki_filp; } ;
struct TYPE_2__ {unsigned int f_flags; } ;

/* Variables and functions */
 int IOCB_DSYNC ; 
 int IOCB_SYNC ; 
 unsigned int O_DSYNC ; 
 unsigned int O_SYNC ; 

__attribute__((used)) static unsigned int fuse_write_flags(struct kiocb *iocb)
{
	unsigned int flags = iocb->ki_filp->f_flags;

	if (iocb->ki_flags & IOCB_DSYNC)
		flags |= O_DSYNC;
	if (iocb->ki_flags & IOCB_SYNC)
		flags |= O_SYNC;

	return flags;
}