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
struct qedf_ctx {int /*<<< orphan*/  flags; } ;
struct fc_vport {struct fc_lport* dd_data; } ;
struct fc_lport {scalar_t__ state; scalar_t__ host; int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  list; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 scalar_t__ LPORT_ST_READY ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_UNLOADING ; 
 int /*<<< orphan*/  fc_exch_mgr_free (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_fabric_logoff (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_destroy (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_free_stats (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_remove_host (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (scalar_t__) ; 
 int /*<<< orphan*/  scsi_remove_host (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

__attribute__((used)) static int qedf_vport_destroy(struct fc_vport *vport)
{
	struct Scsi_Host *shost = vport_to_shost(vport);
	struct fc_lport *n_port = shost_priv(shost);
	struct fc_lport *vn_port = vport->dd_data;
	struct qedf_ctx *qedf = lport_priv(vn_port);

	if (!qedf) {
		QEDF_ERR(NULL, "qedf is NULL.\n");
		goto out;
	}

	/* Set unloading bit on vport qedf_ctx to prevent more I/O */
	set_bit(QEDF_UNLOADING, &qedf->flags);

	mutex_lock(&n_port->lp_mutex);
	list_del(&vn_port->list);
	mutex_unlock(&n_port->lp_mutex);

	fc_fabric_logoff(vn_port);
	fc_lport_destroy(vn_port);

	/* Detach from scsi-ml */
	fc_remove_host(vn_port->host);
	scsi_remove_host(vn_port->host);

	/*
	 * Only try to release the exchange manager if the vn_port
	 * configuration is complete.
	 */
	if (vn_port->state == LPORT_ST_READY)
		fc_exch_mgr_free(vn_port);

	/* Free memory used by statistical counters */
	fc_lport_free_stats(vn_port);

	/* Release Scsi_Host */
	if (vn_port->host)
		scsi_host_put(vn_port->host);

out:
	return 0;
}