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
struct net_device {int dummy; } ;
struct fcoe_port {int /*<<< orphan*/  destroy_work; int /*<<< orphan*/  min_queue_depth; int /*<<< orphan*/  max_queue_depth; int /*<<< orphan*/  get_netdev; struct fcoe_interface* priv; struct fc_lport* lport; } ;
struct fcoe_interface {struct net_device* netdev; } ;
struct fcoe_ctlr {int dummy; } ;
struct fc_vport {int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct fc_lport {int /*<<< orphan*/  host; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fc_lport* ERR_PTR (int) ; 
 int /*<<< orphan*/  FCOE_MAX_QUEUE_DEPTH ; 
 int /*<<< orphan*/  FCOE_MIN_QUEUE_DEPTH ; 
 int /*<<< orphan*/  FCOE_NETDEV_DBG (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fc_vport* dev_to_vport (struct device*) ; 
 int /*<<< orphan*/  fc_exch_mgr_free (struct fc_lport*) ; 
 int fc_exch_mgr_list_clone (struct fc_lport*,struct fc_lport*) ; 
 int /*<<< orphan*/  fc_set_wwnn (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_set_wwpn (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_destroy_work ; 
 int fcoe_em_config (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_fdmi_info (struct fc_lport*,struct net_device*) ; 
 int /*<<< orphan*/  fcoe_hostlist_add (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_hostlist_del (struct fc_lport*) ; 
 int fcoe_libfc_config (struct fc_lport*,struct fcoe_ctlr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fcoe_libfc_fcn_templ ; 
 int fcoe_lport_config (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_netdev ; 
 int fcoe_netdev_config (struct fc_lport*,struct net_device*) ; 
 int fcoe_shost_config (struct fc_lport*,struct device*) ; 
 int /*<<< orphan*/  fcoe_shost_template ; 
 struct fcoe_ctlr* fcoe_to_ctlr (struct fcoe_interface*) ; 
 struct fc_lport* libfc_host_alloc (int /*<<< orphan*/ *,int) ; 
 struct fc_lport* libfc_vport_create (struct fc_vport*,int) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

__attribute__((used)) static struct fc_lport *fcoe_if_create(struct fcoe_interface *fcoe,
				       struct device *parent, int npiv)
{
	struct fcoe_ctlr *ctlr = fcoe_to_ctlr(fcoe);
	struct net_device *netdev = fcoe->netdev;
	struct fc_lport *lport, *n_port;
	struct fcoe_port *port;
	struct Scsi_Host *shost;
	int rc;
	/*
	 * parent is only a vport if npiv is 1,
	 * but we'll only use vport in that case so go ahead and set it
	 */
	struct fc_vport *vport = dev_to_vport(parent);

	FCOE_NETDEV_DBG(netdev, "Create Interface\n");

	if (!npiv)
		lport = libfc_host_alloc(&fcoe_shost_template, sizeof(*port));
	else
		lport = libfc_vport_create(vport, sizeof(*port));

	if (!lport) {
		FCOE_NETDEV_DBG(netdev, "Could not allocate host structure\n");
		rc = -ENOMEM;
		goto out;
	}
	port = lport_priv(lport);
	port->lport = lport;
	port->priv = fcoe;
	port->get_netdev = fcoe_netdev;
	port->max_queue_depth = FCOE_MAX_QUEUE_DEPTH;
	port->min_queue_depth = FCOE_MIN_QUEUE_DEPTH;
	INIT_WORK(&port->destroy_work, fcoe_destroy_work);

	/*
	 * Need to add the lport to the hostlist
	 * so we catch NETDEV_CHANGE events.
	 */
	fcoe_hostlist_add(lport);

	/* configure a fc_lport including the exchange manager */
	rc = fcoe_lport_config(lport);
	if (rc) {
		FCOE_NETDEV_DBG(netdev, "Could not configure lport for the "
				"interface\n");
		goto out_host_put;
	}

	if (npiv) {
		FCOE_NETDEV_DBG(netdev, "Setting vport names, "
				"%16.16llx %16.16llx\n",
				vport->node_name, vport->port_name);
		fc_set_wwnn(lport, vport->node_name);
		fc_set_wwpn(lport, vport->port_name);
	}

	/* configure lport network properties */
	rc = fcoe_netdev_config(lport, netdev);
	if (rc) {
		FCOE_NETDEV_DBG(netdev, "Could not configure netdev for the "
				"interface\n");
		goto out_lp_destroy;
	}

	/* configure lport scsi host properties */
	rc = fcoe_shost_config(lport, parent);
	if (rc) {
		FCOE_NETDEV_DBG(netdev, "Could not configure shost for the "
				"interface\n");
		goto out_lp_destroy;
	}

	/* Initialize the library */
	rc = fcoe_libfc_config(lport, ctlr, &fcoe_libfc_fcn_templ, 1);
	if (rc) {
		FCOE_NETDEV_DBG(netdev, "Could not configure libfc for the "
				"interface\n");
		goto out_lp_destroy;
	}

	/* Initialized FDMI information */
	fcoe_fdmi_info(lport, netdev);

	/*
	 * fcoe_em_alloc() and fcoe_hostlist_add() both
	 * need to be atomic with respect to other changes to the
	 * hostlist since fcoe_em_alloc() looks for an existing EM
	 * instance on host list updated by fcoe_hostlist_add().
	 *
	 * This is currently handled through the fcoe_config_mutex
	 * begin held.
	 */
	if (!npiv)
		/* lport exch manager allocation */
		rc = fcoe_em_config(lport);
	else {
		shost = vport_to_shost(vport);
		n_port = shost_priv(shost);
		rc = fc_exch_mgr_list_clone(n_port, lport);
	}

	if (rc) {
		FCOE_NETDEV_DBG(netdev, "Could not configure the EM\n");
		goto out_lp_destroy;
	}

	return lport;

out_lp_destroy:
	fc_exch_mgr_free(lport);
out_host_put:
	fcoe_hostlist_del(lport);
	scsi_host_put(lport->host);
out:
	return ERR_PTR(rc);
}