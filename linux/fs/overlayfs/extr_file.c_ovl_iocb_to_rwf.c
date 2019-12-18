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
struct kiocb {int ki_flags; } ;
typedef  int /*<<< orphan*/  rwf_t ;

/* Variables and functions */
 int IOCB_DSYNC ; 
 int IOCB_HIPRI ; 
 int IOCB_NOWAIT ; 
 int IOCB_SYNC ; 
 int /*<<< orphan*/  RWF_DSYNC ; 
 int /*<<< orphan*/  RWF_HIPRI ; 
 int /*<<< orphan*/  RWF_NOWAIT ; 
 int /*<<< orphan*/  RWF_SYNC ; 

__attribute__((used)) static rwf_t ovl_iocb_to_rwf(struct kiocb *iocb)
{
	int ifl = iocb->ki_flags;
	rwf_t flags = 0;

	if (ifl & IOCB_NOWAIT)
		flags |= RWF_NOWAIT;
	if (ifl & IOCB_HIPRI)
		flags |= RWF_HIPRI;
	if (ifl & IOCB_DSYNC)
		flags |= RWF_DSYNC;
	if (ifl & IOCB_SYNC)
		flags |= RWF_SYNC;

	return flags;
}