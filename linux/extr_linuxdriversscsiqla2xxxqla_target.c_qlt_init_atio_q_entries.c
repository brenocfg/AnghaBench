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
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct TYPE_4__ {scalar_t__ atio_q_length; scalar_t__ atio_ring; } ;
struct qla_hw_data {TYPE_1__ tgt; } ;
struct TYPE_5__ {int /*<<< orphan*/  signature; } ;
struct TYPE_6__ {TYPE_2__ raw; } ;
struct atio_from_isp {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIO_PROCESSED ; 
 scalar_t__ qla_ini_mode_enabled (struct scsi_qla_host*) ; 

void
qlt_init_atio_q_entries(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint16_t cnt;
	struct atio_from_isp *pkt = (struct atio_from_isp *)ha->tgt.atio_ring;

	if (qla_ini_mode_enabled(vha))
		return;

	for (cnt = 0; cnt < ha->tgt.atio_q_length; cnt++) {
		pkt->u.raw.signature = ATIO_PROCESSED;
		pkt++;
	}

}