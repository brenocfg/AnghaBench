#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  loop_state; TYPE_1__* hw; int /*<<< orphan*/  host; int /*<<< orphan*/  dpc_flags; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_4__ {unsigned long loop_reset_delay; } ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ LOOP_READY ; 
 int /*<<< orphan*/  UNLOADING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla2xxx_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	if (test_bit(UNLOADING, &vha->dpc_flags))
		return 1;
	if (!vha->host)
		return 1;
	if (time > vha->hw->loop_reset_delay * HZ)
		return 1;

	return atomic_read(&vha->loop_state) == LOOP_READY;
}