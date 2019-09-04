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
typedef  scalar_t__ u8 ;
struct net {int dummy; } ;
struct cflayer {scalar_t__ id; int /*<<< orphan*/  (* ctrlcmd ) (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct cfcnfg {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_DEINIT_RSP ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfctrl_cancel_req (int /*<<< orphan*/ ,struct cflayer*) ; 
 int /*<<< orphan*/  cfctrl_linkdown_req (int /*<<< orphan*/ ,scalar_t__,struct cflayer*) ; 
 struct cflayer* cfmuxl_remove_uplayer (int /*<<< orphan*/ ,scalar_t__) ; 
 struct cfcnfg* get_cfcnfg (struct net*) ; 
 int /*<<< orphan*/  layer_set_up (struct cflayer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  stub1 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int caif_disconnect_client(struct net *net, struct cflayer *adap_layer)
{
	u8 channel_id;
	struct cfcnfg *cfg = get_cfcnfg(net);

	caif_assert(adap_layer != NULL);
	cfctrl_cancel_req(cfg->ctrl, adap_layer);
	channel_id = adap_layer->id;
	if (channel_id != 0) {
		struct cflayer *servl;
		servl = cfmuxl_remove_uplayer(cfg->mux, channel_id);
		cfctrl_linkdown_req(cfg->ctrl, channel_id, adap_layer);
		if (servl != NULL)
			layer_set_up(servl, NULL);
	} else
		pr_debug("nothing to disconnect\n");

	/* Do RCU sync before initiating cleanup */
	synchronize_rcu();
	if (adap_layer->ctrlcmd != NULL)
		adap_layer->ctrlcmd(adap_layer, CAIF_CTRLCMD_DEINIT_RSP, 0);
	return 0;

}