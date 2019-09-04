#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_param {int /*<<< orphan*/  value; } ;
struct iscsi_conn_ops {scalar_t__ MaxRecvDataSegmentLength; } ;
struct iscsi_conn {TYPE_3__* sess; int /*<<< orphan*/  param_list; TYPE_1__* login; struct iscsi_conn_ops* conn_ops; struct cxgbit_sock* context; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; struct cxgbit_device* cdev; } ;
struct cxgbit_sock {TYPE_6__ com; } ;
struct TYPE_10__ {int /*<<< orphan*/  adapter_type; struct cxgbi_ppm** iscsi_ppm; } ;
struct cxgbit_device {scalar_t__ mdsl; int /*<<< orphan*/  flags; TYPE_4__ lldi; } ;
struct TYPE_11__ {int /*<<< orphan*/  pgsz_idx_dflt; } ;
struct cxgbi_ppm {TYPE_5__ tformat; } ;
struct TYPE_9__ {TYPE_2__* sess_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  ErrorRecoveryLevel; } ;
struct TYPE_7__ {scalar_t__ leading_connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_DDP_ENABLE ; 
 int /*<<< orphan*/  CDEV_ISO_ENABLE ; 
 int /*<<< orphan*/  CSK_DDP_ENABLE ; 
 int /*<<< orphan*/  ERRORRECOVERYLEVEL ; 
 int cxgbit_seq_pdu_inorder (struct cxgbit_sock*) ; 
 scalar_t__ cxgbit_set_digest (struct cxgbit_sock*) ; 
 scalar_t__ cxgbit_set_iso_npdu (struct cxgbit_sock*) ; 
 scalar_t__ cxgbit_setup_conn_pgidx (struct cxgbit_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 struct iscsi_param* iscsi_find_param_from_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtou8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxgbit_set_params(struct iscsi_conn *conn)
{
	struct cxgbit_sock *csk = conn->context;
	struct cxgbit_device *cdev = csk->com.cdev;
	struct cxgbi_ppm *ppm = *csk->com.cdev->lldi.iscsi_ppm;
	struct iscsi_conn_ops *conn_ops = conn->conn_ops;
	struct iscsi_param *param;
	u8 erl;

	if (conn_ops->MaxRecvDataSegmentLength > cdev->mdsl)
		conn_ops->MaxRecvDataSegmentLength = cdev->mdsl;

	if (cxgbit_set_digest(csk))
		return -1;

	if (conn->login->leading_connection) {
		param = iscsi_find_param_from_key(ERRORRECOVERYLEVEL,
						  conn->param_list);
		if (!param) {
			pr_err("param not found key %s\n", ERRORRECOVERYLEVEL);
			return -1;
		}
		if (kstrtou8(param->value, 0, &erl) < 0)
			return -1;
	} else {
		erl = conn->sess->sess_ops->ErrorRecoveryLevel;
	}

	if (!erl) {
		int ret;

		ret = cxgbit_seq_pdu_inorder(csk);
		if (ret < 0) {
			return -1;
		} else if (ret > 0) {
			if (is_t5(cdev->lldi.adapter_type))
				goto enable_ddp;
			else
				return 0;
		}

		if (test_bit(CDEV_ISO_ENABLE, &cdev->flags)) {
			if (cxgbit_set_iso_npdu(csk))
				return -1;
		}

enable_ddp:
		if (test_bit(CDEV_DDP_ENABLE, &cdev->flags)) {
			if (cxgbit_setup_conn_pgidx(csk,
						    ppm->tformat.pgsz_idx_dflt))
				return -1;
			set_bit(CSK_DDP_ENABLE, &csk->com.flags);
		}
	}

	return 0;
}