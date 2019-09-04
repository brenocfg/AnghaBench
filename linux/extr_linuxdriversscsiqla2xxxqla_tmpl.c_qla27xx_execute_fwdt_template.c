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
typedef  int /*<<< orphan*/  ulong ;
struct scsi_qla_host {TYPE_1__* hw; } ;
struct qla27xx_fwdt_template {int /*<<< orphan*/  template_size; } ;
struct TYPE_2__ {int fw_dumped; int /*<<< orphan*/  fw_dump_len; int /*<<< orphan*/  fw_dump; struct qla27xx_fwdt_template* fw_dump_template; } ;

/* Variables and functions */
 struct qla27xx_fwdt_template* memcpy (int /*<<< orphan*/ ,struct qla27xx_fwdt_template*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql27xx_edit_template (struct scsi_qla_host*,struct qla27xx_fwdt_template*) ; 
 scalar_t__ qla27xx_fwdt_template_valid (struct qla27xx_fwdt_template*) ; 
 int /*<<< orphan*/  qla27xx_walk_template (struct scsi_qla_host*,struct qla27xx_fwdt_template*,struct qla27xx_fwdt_template*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla27xx_execute_fwdt_template(struct scsi_qla_host *vha)
{
	struct qla27xx_fwdt_template *tmp = vha->hw->fw_dump_template;
	ulong len;

	if (qla27xx_fwdt_template_valid(tmp)) {
		len = tmp->template_size;
		tmp = memcpy(vha->hw->fw_dump, tmp, len);
		ql27xx_edit_template(vha, tmp);
		qla27xx_walk_template(vha, tmp, tmp, &len);
		vha->hw->fw_dump_len = len;
		vha->hw->fw_dumped = 1;
	}
}