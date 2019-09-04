#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fcoe_rport {int /*<<< orphan*/  login_count; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_id; } ;
struct fc_rport_priv {TYPE_2__ ids; } ;
struct TYPE_3__ {struct fcoe_ctlr* priv; } ;
struct fc_lport {TYPE_1__ disc; } ;
typedef  enum fc_rport_event { ____Placeholder_fc_rport_event } fc_rport_event ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_CTLR_VN2VN_LOGIN_LIMIT ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,int /*<<< orphan*/ ,...) ; 
#define  RPORT_EV_FAILED 131 
#define  RPORT_EV_LOGO 130 
#define  RPORT_EV_READY 129 
#define  RPORT_EV_STOP 128 
 int /*<<< orphan*/  fc_rport_logoff (struct fc_rport_priv*) ; 
 struct fcoe_rport* fcoe_ctlr_rport (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fcoe_ctlr_vn_rport_callback(struct fc_lport *lport,
					struct fc_rport_priv *rdata,
					enum fc_rport_event event)
{
	struct fcoe_ctlr *fip = lport->disc.priv;
	struct fcoe_rport *frport = fcoe_ctlr_rport(rdata);

	LIBFCOE_FIP_DBG(fip, "vn_rport_callback %x event %d\n",
			rdata->ids.port_id, event);

	mutex_lock(&fip->ctlr_mutex);
	switch (event) {
	case RPORT_EV_READY:
		frport->login_count = 0;
		break;
	case RPORT_EV_LOGO:
	case RPORT_EV_FAILED:
	case RPORT_EV_STOP:
		frport->login_count++;
		if (frport->login_count > FCOE_CTLR_VN2VN_LOGIN_LIMIT) {
			LIBFCOE_FIP_DBG(fip,
					"rport FLOGI limited port_id %6.6x\n",
					rdata->ids.port_id);
			fc_rport_logoff(rdata);
		}
		break;
	default:
		break;
	}
	mutex_unlock(&fip->ctlr_mutex);
}