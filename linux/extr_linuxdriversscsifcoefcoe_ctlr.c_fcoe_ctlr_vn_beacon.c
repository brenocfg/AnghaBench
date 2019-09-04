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
struct fcoe_rport {int flags; scalar_t__ time; } ;
struct fcoe_ctlr {scalar_t__ state; scalar_t__ sol_time; struct fc_lport* lp; } ;
struct TYPE_2__ {scalar_t__ node_name; scalar_t__ port_name; int /*<<< orphan*/  port_id; } ;
struct fc_rport_priv {TYPE_1__ ids; int /*<<< orphan*/  kref; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
 int FIP_FL_REC_OR_P2P ; 
 int /*<<< orphan*/  FIP_SC_VN_PROBE_REQ ; 
 scalar_t__ FIP_ST_VNMP_UP ; 
 int /*<<< orphan*/  FIP_VN_ANN_WAIT ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,...) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_login (struct fc_rport_priv*) ; 
 struct fc_rport_priv* fc_rport_lookup (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_all_vn2vn ; 
 struct fcoe_rport* fcoe_ctlr_rport (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send (struct fcoe_ctlr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send_claim (struct fcoe_ctlr*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void fcoe_ctlr_vn_beacon(struct fcoe_ctlr *fip,
				struct fc_rport_priv *new)
{
	struct fc_lport *lport = fip->lp;
	struct fc_rport_priv *rdata;
	struct fcoe_rport *frport;

	frport = fcoe_ctlr_rport(new);
	if (frport->flags & FIP_FL_REC_OR_P2P) {
		LIBFCOE_FIP_DBG(fip, "p2p beacon while in vn2vn mode\n");
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		return;
	}
	rdata = fc_rport_lookup(lport, new->ids.port_id);
	if (rdata) {
		if (rdata->ids.node_name == new->ids.node_name &&
		    rdata->ids.port_name == new->ids.port_name) {
			frport = fcoe_ctlr_rport(rdata);
			LIBFCOE_FIP_DBG(fip, "beacon from rport %x\n",
					rdata->ids.port_id);
			if (!frport->time && fip->state == FIP_ST_VNMP_UP) {
				LIBFCOE_FIP_DBG(fip, "beacon expired "
						"for rport %x\n",
						rdata->ids.port_id);
				fc_rport_login(rdata);
			}
			frport->time = jiffies;
		}
		kref_put(&rdata->kref, fc_rport_destroy);
		return;
	}
	if (fip->state != FIP_ST_VNMP_UP)
		return;

	/*
	 * Beacon from a new neighbor.
	 * Send a claim notify if one hasn't been sent recently.
	 * Don't add the neighbor yet.
	 */
	LIBFCOE_FIP_DBG(fip, "beacon from new rport %x. sending claim notify\n",
			new->ids.port_id);
	if (time_after(jiffies,
		       fip->sol_time + msecs_to_jiffies(FIP_VN_ANN_WAIT)))
		fcoe_ctlr_vn_send_claim(fip);
}