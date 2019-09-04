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
struct scsi_qla_host {TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  srb_t ;
struct TYPE_2__ {int /*<<< orphan*/  base_qpair; } ;

/* Variables and functions */
 void* __qla2x00_alloc_iocbs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *
qla2x00_alloc_iocbs(struct scsi_qla_host *vha, srb_t *sp)
{
	return __qla2x00_alloc_iocbs(vha->hw->base_qpair, sp);
}