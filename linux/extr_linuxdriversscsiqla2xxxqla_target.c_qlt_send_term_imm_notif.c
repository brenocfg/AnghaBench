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
struct imm_ntfy_from_isp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hardware_lock; } ;

/* Variables and functions */
 int __qlt_send_term_imm_notif (struct scsi_qla_host*,struct imm_ntfy_from_isp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qlt_send_term_imm_notif(struct scsi_qla_host *vha,
	struct imm_ntfy_from_isp *imm, int ha_locked)
{
	unsigned long flags = 0;
	int rc;

	if (ha_locked) {
		rc = __qlt_send_term_imm_notif(vha, imm);

#if 0	/* Todo  */
		if (rc == -ENOMEM)
			qlt_alloc_qfull_cmd(vha, imm, 0, 0);
#else
		if (rc) {
		}
#endif
		goto done;
	}

	spin_lock_irqsave(&vha->hw->hardware_lock, flags);
	rc = __qlt_send_term_imm_notif(vha, imm);

#if 0	/* Todo */
	if (rc == -ENOMEM)
		qlt_alloc_qfull_cmd(vha, imm, 0, 0);
#endif

done:
	if (!ha_locked)
		spin_unlock_irqrestore(&vha->hw->hardware_lock, flags);
}