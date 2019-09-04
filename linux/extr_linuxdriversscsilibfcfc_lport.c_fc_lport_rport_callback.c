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
struct TYPE_2__ {int port_id; } ;
struct fc_rport_priv {TYPE_1__ ids; } ;
struct fc_lport {int state; int /*<<< orphan*/  lp_mutex; struct fc_rport_priv* ms_rdata; struct fc_rport_priv* dns_rdata; } ;
typedef  enum fc_rport_event { ____Placeholder_fc_rport_event } fc_rport_event ;

/* Variables and functions */
 int FC_FID_DIR_SERV ; 
 int FC_FID_MGMT_SERV ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int,int) ; 
 int /*<<< orphan*/  LPORT_ST_DHBA ; 
 int LPORT_ST_DNS ; 
 int LPORT_ST_FDMI ; 
 int /*<<< orphan*/  LPORT_ST_RNN_ID ; 
#define  RPORT_EV_FAILED 132 
#define  RPORT_EV_LOGO 131 
#define  RPORT_EV_NONE 130 
#define  RPORT_EV_READY 129 
#define  RPORT_EV_STOP 128 
 int /*<<< orphan*/  fc_lport_enter_ms (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_lport_enter_ns (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_logoff (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_lport_rport_callback(struct fc_lport *lport,
				    struct fc_rport_priv *rdata,
				    enum fc_rport_event event)
{
	FC_LPORT_DBG(lport, "Received a %d event for port (%6.6x)\n", event,
		     rdata->ids.port_id);

	mutex_lock(&lport->lp_mutex);
	switch (event) {
	case RPORT_EV_READY:
		if (lport->state == LPORT_ST_DNS) {
			lport->dns_rdata = rdata;
			fc_lport_enter_ns(lport, LPORT_ST_RNN_ID);
		} else if (lport->state == LPORT_ST_FDMI) {
			lport->ms_rdata = rdata;
			fc_lport_enter_ms(lport, LPORT_ST_DHBA);
		} else {
			FC_LPORT_DBG(lport, "Received an READY event "
				     "on port (%6.6x) for the directory "
				     "server, but the lport is not "
				     "in the DNS or FDMI state, it's in the "
				     "%d state", rdata->ids.port_id,
				     lport->state);
			fc_rport_logoff(rdata);
		}
		break;
	case RPORT_EV_LOGO:
	case RPORT_EV_FAILED:
	case RPORT_EV_STOP:
		if (rdata->ids.port_id == FC_FID_DIR_SERV)
			lport->dns_rdata = NULL;
		else if (rdata->ids.port_id == FC_FID_MGMT_SERV)
			lport->ms_rdata = NULL;
		break;
	case RPORT_EV_NONE:
		break;
	}
	mutex_unlock(&lport->lp_mutex);
}