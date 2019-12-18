#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct cflayer {int /*<<< orphan*/  (* ctrlcmd ) (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  id; } ;
struct TYPE_9__ {struct net_device* dev; } ;
struct cfcnfg_phyinfo {TYPE_2__ dev_info; TYPE_1__* phy_layer; int /*<<< orphan*/  id; } ;
struct cfcnfg {struct cflayer* mux; int /*<<< orphan*/  ctrl; } ;
typedef  enum cfctrl_srv { ____Placeholder_cfctrl_srv } cfctrl_srv ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_INIT_FAIL_RSP ; 
 int /*<<< orphan*/  CAIF_CTRLCMD_INIT_RSP ; 
#define  CFCTRL_SRV_DATAGRAM 133 
#define  CFCTRL_SRV_DBG 132 
#define  CFCTRL_SRV_RFM 131 
#define  CFCTRL_SRV_UTIL 130 
#define  CFCTRL_SRV_VEI 129 
#define  CFCTRL_SRV_VIDEO 128 
 int /*<<< orphan*/  caif_assert (int) ; 
 struct cfcnfg_phyinfo* cfcnfg_get_phyinfo_rcu (struct cfcnfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfctrl_linkdown_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cflayer* cfdbgl_create (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct cflayer* cfdgml_create (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cfmuxl_set_uplayer (struct cflayer*,struct cflayer*,int /*<<< orphan*/ ) ; 
 struct cflayer* cfrfml_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct cflayer* cfutill_create (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct cflayer* cfvei_create (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct cflayer* cfvidl_create (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct cfcnfg* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  layer_set_dn (struct cflayer*,struct cflayer*) ; 
 int /*<<< orphan*/  layer_set_up (struct cflayer*,struct cflayer*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cfcnfg_linkup_rsp(struct cflayer *layer, u8 channel_id, enum cfctrl_srv serv,
		  u8 phyid, struct cflayer *adapt_layer)
{
	struct cfcnfg *cnfg = container_obj(layer);
	struct cflayer *servicel = NULL;
	struct cfcnfg_phyinfo *phyinfo;
	struct net_device *netdev;

	if (channel_id == 0) {
		pr_warn("received channel_id zero\n");
		if (adapt_layer != NULL && adapt_layer->ctrlcmd != NULL)
			adapt_layer->ctrlcmd(adapt_layer,
						CAIF_CTRLCMD_INIT_FAIL_RSP, 0);
		return;
	}

	rcu_read_lock();

	if (adapt_layer == NULL) {
		pr_debug("link setup response but no client exist, send linkdown back\n");
		cfctrl_linkdown_req(cnfg->ctrl, channel_id, NULL);
		goto unlock;
	}

	caif_assert(cnfg != NULL);
	caif_assert(phyid != 0);

	phyinfo = cfcnfg_get_phyinfo_rcu(cnfg, phyid);
	if (phyinfo == NULL) {
		pr_err("ERROR: Link Layer Device disappeared while connecting\n");
		goto unlock;
	}

	caif_assert(phyinfo != NULL);
	caif_assert(phyinfo->id == phyid);
	caif_assert(phyinfo->phy_layer != NULL);
	caif_assert(phyinfo->phy_layer->id == phyid);

	adapt_layer->id = channel_id;

	switch (serv) {
	case CFCTRL_SRV_VEI:
		servicel = cfvei_create(channel_id, &phyinfo->dev_info);
		break;
	case CFCTRL_SRV_DATAGRAM:
		servicel = cfdgml_create(channel_id,
					&phyinfo->dev_info);
		break;
	case CFCTRL_SRV_RFM:
		netdev = phyinfo->dev_info.dev;
		servicel = cfrfml_create(channel_id, &phyinfo->dev_info,
						netdev->mtu);
		break;
	case CFCTRL_SRV_UTIL:
		servicel = cfutill_create(channel_id, &phyinfo->dev_info);
		break;
	case CFCTRL_SRV_VIDEO:
		servicel = cfvidl_create(channel_id, &phyinfo->dev_info);
		break;
	case CFCTRL_SRV_DBG:
		servicel = cfdbgl_create(channel_id, &phyinfo->dev_info);
		break;
	default:
		pr_err("Protocol error. Link setup response - unknown channel type\n");
		goto unlock;
	}
	if (!servicel)
		goto unlock;
	layer_set_dn(servicel, cnfg->mux);
	cfmuxl_set_uplayer(cnfg->mux, servicel, channel_id);
	layer_set_up(servicel, adapt_layer);
	layer_set_dn(adapt_layer, servicel);

	rcu_read_unlock();

	servicel->ctrlcmd(servicel, CAIF_CTRLCMD_INIT_RSP, 0);
	return;
unlock:
	rcu_read_unlock();
}