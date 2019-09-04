#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct se_portal_group {TYPE_2__* tpg_virt_lun0; } ;
struct se_device {TYPE_3__* transport; } ;
struct se_cmd {unsigned char* t_task_cdb; int /*<<< orphan*/  data_length; TYPE_1__* se_lun; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_9__ {unsigned char page; int /*<<< orphan*/  (* emulate ) (struct se_cmd*,unsigned char*) ;} ;
struct TYPE_8__ {unsigned char (* get_device_type ) (struct se_device*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  lun_se_dev; } ;
struct TYPE_6__ {struct se_portal_group* lun_tpg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  SE_INQUIRY_BUF ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 TYPE_4__* evpd_handlers ; 
 int get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct se_device* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spc_emulate_inquiry_std (struct se_cmd*,unsigned char*) ; 
 unsigned char stub1 (struct se_device*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  target_complete_cmd_with_length (struct se_cmd*,int /*<<< orphan*/ ,int) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static sense_reason_t
spc_emulate_inquiry(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct se_portal_group *tpg = cmd->se_lun->lun_tpg;
	unsigned char *rbuf;
	unsigned char *cdb = cmd->t_task_cdb;
	unsigned char *buf;
	sense_reason_t ret;
	int p;
	int len = 0;

	buf = kzalloc(SE_INQUIRY_BUF, GFP_KERNEL);
	if (!buf) {
		pr_err("Unable to allocate response buffer for INQUIRY\n");
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	if (dev == rcu_access_pointer(tpg->tpg_virt_lun0->lun_se_dev))
		buf[0] = 0x3f; /* Not connected */
	else
		buf[0] = dev->transport->get_device_type(dev);

	if (!(cdb[1] & 0x1)) {
		if (cdb[2]) {
			pr_err("INQUIRY with EVPD==0 but PAGE CODE=%02x\n",
			       cdb[2]);
			ret = TCM_INVALID_CDB_FIELD;
			goto out;
		}

		ret = spc_emulate_inquiry_std(cmd, buf);
		len = buf[4] + 5;
		goto out;
	}

	for (p = 0; p < ARRAY_SIZE(evpd_handlers); ++p) {
		if (cdb[2] == evpd_handlers[p].page) {
			buf[1] = cdb[2];
			ret = evpd_handlers[p].emulate(cmd, buf);
			len = get_unaligned_be16(&buf[2]) + 4;
			goto out;
		}
	}

	pr_err("Unknown VPD Code: 0x%02x\n", cdb[2]);
	ret = TCM_INVALID_CDB_FIELD;

out:
	rbuf = transport_kmap_data_sg(cmd);
	if (rbuf) {
		memcpy(rbuf, buf, min_t(u32, SE_INQUIRY_BUF, cmd->data_length));
		transport_kunmap_data_sg(cmd);
	}
	kfree(buf);

	if (!ret)
		target_complete_cmd_with_length(cmd, GOOD, len);
	return ret;
}