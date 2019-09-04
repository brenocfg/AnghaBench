#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_QLAFX00 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_loop_reset (TYPE_1__*) ; 
 TYPE_1__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla2x00_issue_lip(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	if (IS_QLAFX00(vha->hw))
		return 0;

	qla2x00_loop_reset(vha);
	return 0;
}