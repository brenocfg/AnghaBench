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
struct scsi_cmnd {TYPE_1__* request; } ;
struct fib {int /*<<< orphan*/ * callback; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/  type; TYPE_3__* hw_fib_va; } ;
struct aac_dev {struct fib* fibs; } ;
struct TYPE_5__ {scalar_t__ XferState; } ;
struct TYPE_6__ {TYPE_2__ header; } ;
struct TYPE_4__ {size_t tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSAFS_NTC_FIB_CONTEXT ; 

struct fib *aac_fib_alloc_tag(struct aac_dev *dev, struct scsi_cmnd *scmd)
{
	struct fib *fibptr;

	fibptr = &dev->fibs[scmd->request->tag];
	/*
	 *	Null out fields that depend on being zero at the start of
	 *	each I/O
	 */
	fibptr->hw_fib_va->header.XferState = 0;
	fibptr->type = FSAFS_NTC_FIB_CONTEXT;
	fibptr->callback_data = NULL;
	fibptr->callback = NULL;

	return fibptr;
}