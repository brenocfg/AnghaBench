#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rq_list_lock; } ;
struct TYPE_5__ {int done; } ;
typedef  TYPE_1__ Sg_request ;
typedef  TYPE_2__ Sg_fd ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int srp_done(Sg_fd *sfp, Sg_request *srp)
{
	unsigned long flags;
	int ret;

	read_lock_irqsave(&sfp->rq_list_lock, flags);
	ret = srp->done;
	read_unlock_irqrestore(&sfp->rq_list_lock, flags);
	return ret;
}