#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  int uint32_t ;
typedef  scalar_t__ uint ;
struct TYPE_13__ {TYPE_4__* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
struct TYPE_12__ {TYPE_3__* iobase; TYPE_1__* pdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  hccr; } ;
struct TYPE_11__ {TYPE_2__ isp24; } ;
struct TYPE_9__ {int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCCRX_SET_RISC_PAUSE ; 
 int RISC_SEMAPHORE ; 
 int /*<<< orphan*/  RISC_SEMAPHORE_CLR ; 
 int RISC_SEMAPHORE_FORCE ; 
 int /*<<< orphan*/  RISC_SEMAPHORE_FORCE_CLR ; 
 int /*<<< orphan*/  RISC_SEMAPHORE_FORCE_SET ; 
 int /*<<< orphan*/  RISC_SEMAPHORE_SET ; 
 scalar_t__ TIMEOUT_SEMAPHORE ; 
 scalar_t__ TIMEOUT_SEMAPHORE_FORCE ; 
 scalar_t__ TIMEOUT_TOTAL_ELAPSED ; 
 int /*<<< orphan*/  WRT_REG_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  qla25xx_read_risc_sema_reg (TYPE_5__*,int*) ; 
 int /*<<< orphan*/  qla25xx_write_risc_sema_reg (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
qla25xx_manipulate_risc_semaphore(scsi_qla_host_t *vha)
{
	uint32_t wd32 = 0;
	uint delta_msec = 100;
	uint elapsed_msec = 0;
	uint timeout_msec;
	ulong n;

	if (vha->hw->pdev->subsystem_device != 0x0175 &&
	    vha->hw->pdev->subsystem_device != 0x0240)
		return;

	WRT_REG_DWORD(&vha->hw->iobase->isp24.hccr, HCCRX_SET_RISC_PAUSE);
	udelay(100);

attempt:
	timeout_msec = TIMEOUT_SEMAPHORE;
	n = timeout_msec / delta_msec;
	while (n--) {
		qla25xx_write_risc_sema_reg(vha, RISC_SEMAPHORE_SET);
		qla25xx_read_risc_sema_reg(vha, &wd32);
		if (wd32 & RISC_SEMAPHORE)
			break;
		msleep(delta_msec);
		elapsed_msec += delta_msec;
		if (elapsed_msec > TIMEOUT_TOTAL_ELAPSED)
			goto force;
	}

	if (!(wd32 & RISC_SEMAPHORE))
		goto force;

	if (!(wd32 & RISC_SEMAPHORE_FORCE))
		goto acquired;

	qla25xx_write_risc_sema_reg(vha, RISC_SEMAPHORE_CLR);
	timeout_msec = TIMEOUT_SEMAPHORE_FORCE;
	n = timeout_msec / delta_msec;
	while (n--) {
		qla25xx_read_risc_sema_reg(vha, &wd32);
		if (!(wd32 & RISC_SEMAPHORE_FORCE))
			break;
		msleep(delta_msec);
		elapsed_msec += delta_msec;
		if (elapsed_msec > TIMEOUT_TOTAL_ELAPSED)
			goto force;
	}

	if (wd32 & RISC_SEMAPHORE_FORCE)
		qla25xx_write_risc_sema_reg(vha, RISC_SEMAPHORE_FORCE_CLR);

	goto attempt;

force:
	qla25xx_write_risc_sema_reg(vha, RISC_SEMAPHORE_FORCE_SET);

acquired:
	return;
}