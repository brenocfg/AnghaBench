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
struct cflayer {int /*<<< orphan*/  id; } ;
struct cfcnfg_phyinfo {int up; int /*<<< orphan*/  frm_layer; } ;
struct cfcnfg {int /*<<< orphan*/  mux; } ;

/* Variables and functions */
 int ENODEV ; 
 struct cfcnfg_phyinfo* cfcnfg_get_phyinfo_rcu (struct cfcnfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cffrml_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cffrml_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfmuxl_remove_dnlayer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfmuxl_set_dnlayer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int cfcnfg_set_phy_state(struct cfcnfg *cnfg, struct cflayer *phy_layer,
			 bool up)
{
	struct cfcnfg_phyinfo *phyinfo;

	rcu_read_lock();
	phyinfo = cfcnfg_get_phyinfo_rcu(cnfg, phy_layer->id);
	if (phyinfo == NULL) {
		rcu_read_unlock();
		return -ENODEV;
	}

	if (phyinfo->up == up) {
		rcu_read_unlock();
		return 0;
	}
	phyinfo->up = up;

	if (up) {
		cffrml_hold(phyinfo->frm_layer);
		cfmuxl_set_dnlayer(cnfg->mux, phyinfo->frm_layer,
					phy_layer->id);
	} else {
		cfmuxl_remove_dnlayer(cnfg->mux, phy_layer->id);
		cffrml_put(phyinfo->frm_layer);
	}

	rcu_read_unlock();
	return 0;
}