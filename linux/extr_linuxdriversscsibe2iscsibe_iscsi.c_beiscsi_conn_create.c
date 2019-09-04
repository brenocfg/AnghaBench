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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_session {struct beiscsi_session* dd_data; } ;
struct iscsi_conn {struct beiscsi_conn* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct beiscsi_session {int dummy; } ;
struct beiscsi_hba {int dummy; } ;
struct beiscsi_conn {struct beiscsi_session* beiscsi_sess; struct iscsi_conn* conn; struct beiscsi_hba* phba; int /*<<< orphan*/ * ep; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct iscsi_cls_conn* iscsi_conn_setup (struct iscsi_cls_session*,int,int /*<<< orphan*/ ) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 

struct iscsi_cls_conn *
beiscsi_conn_create(struct iscsi_cls_session *cls_session, u32 cid)
{
	struct beiscsi_hba *phba;
	struct Scsi_Host *shost;
	struct iscsi_cls_conn *cls_conn;
	struct beiscsi_conn *beiscsi_conn;
	struct iscsi_conn *conn;
	struct iscsi_session *sess;
	struct beiscsi_session *beiscsi_sess;

	shost = iscsi_session_to_shost(cls_session);
	phba = iscsi_host_priv(shost);

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_create ,cid"
		    "from iscsi layer=%d\n", cid);

	cls_conn = iscsi_conn_setup(cls_session, sizeof(*beiscsi_conn), cid);
	if (!cls_conn)
		return NULL;

	conn = cls_conn->dd_data;
	beiscsi_conn = conn->dd_data;
	beiscsi_conn->ep = NULL;
	beiscsi_conn->phba = phba;
	beiscsi_conn->conn = conn;
	sess = cls_session->dd_data;
	beiscsi_sess = sess->dd_data;
	beiscsi_conn->beiscsi_sess = beiscsi_sess;
	return cls_conn;
}