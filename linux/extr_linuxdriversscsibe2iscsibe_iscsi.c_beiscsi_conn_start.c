#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iscsi_conn {struct beiscsi_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct beiscsi_offload_params {int dummy; } ;
struct beiscsi_hba {int /*<<< orphan*/  state; } ;
struct beiscsi_endpoint {int dummy; } ;
struct beiscsi_conn {scalar_t__ login_in_progress; struct beiscsi_hba* phba; struct beiscsi_endpoint* ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int EBUSY ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_hba_is_online (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  beiscsi_offload_connection (struct beiscsi_conn*,struct beiscsi_offload_params*) ; 
 int /*<<< orphan*/  beiscsi_set_params_for_offld (struct beiscsi_conn*,struct beiscsi_offload_params*) ; 
 int /*<<< orphan*/  iscsi_conn_start (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  memset (struct beiscsi_offload_params*,int /*<<< orphan*/ ,int) ; 

int beiscsi_conn_start(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct beiscsi_conn *beiscsi_conn = conn->dd_data;
	struct beiscsi_endpoint *beiscsi_ep;
	struct beiscsi_offload_params params;
	struct beiscsi_hba *phba;

	phba = ((struct beiscsi_conn *)conn->dd_data)->phba;

	if (!beiscsi_hba_is_online(phba)) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		return -EBUSY;
	}
	beiscsi_log(beiscsi_conn->phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_start\n");

	memset(&params, 0, sizeof(struct beiscsi_offload_params));
	beiscsi_ep = beiscsi_conn->ep;
	if (!beiscsi_ep)
		beiscsi_log(beiscsi_conn->phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG,
			    "BS_%d : In beiscsi_conn_start , no beiscsi_ep\n");

	beiscsi_conn->login_in_progress = 0;
	beiscsi_set_params_for_offld(beiscsi_conn, &params);
	beiscsi_offload_connection(beiscsi_conn, &params);
	iscsi_conn_start(cls_conn);
	return 0;
}