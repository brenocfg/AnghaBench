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
typedef  scalar_t__ u16 ;
struct cflayer {scalar_t__ id; struct cflayer* phy_layer; struct cflayer* dn; struct cflayer* frm_layer; int /*<<< orphan*/  node; } ;
struct cfcnfg_phyinfo {scalar_t__ id; struct cfcnfg_phyinfo* phy_layer; struct cfcnfg_phyinfo* dn; struct cfcnfg_phyinfo* frm_layer; int /*<<< orphan*/  node; } ;
struct cfcnfg {int /*<<< orphan*/  lock; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  caif_assert (int) ; 
 struct cflayer* cfcnfg_get_phyinfo_rcu (struct cfcnfg*,scalar_t__) ; 
 int /*<<< orphan*/  cffrml_free (struct cflayer*) ; 
 scalar_t__ cffrml_refcnt_read (struct cflayer*) ; 
 int /*<<< orphan*/  cffrml_set_dnlayer (struct cflayer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cffrml_set_uplayer (struct cflayer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cflayer*) ; 
 int /*<<< orphan*/  layer_set_dn (struct cflayer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_set_up (struct cflayer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int cfcnfg_del_phy_layer(struct cfcnfg *cnfg, struct cflayer *phy_layer)
{
	struct cflayer *frml, *frml_dn;
	u16 phyid;
	struct cfcnfg_phyinfo *phyinfo;

	might_sleep();

	mutex_lock(&cnfg->lock);

	phyid = phy_layer->id;
	phyinfo = cfcnfg_get_phyinfo_rcu(cnfg, phyid);

	if (phyinfo == NULL) {
		mutex_unlock(&cnfg->lock);
		return 0;
	}
	caif_assert(phyid == phyinfo->id);
	caif_assert(phy_layer == phyinfo->phy_layer);
	caif_assert(phy_layer->id == phyid);
	caif_assert(phyinfo->frm_layer->id == phyid);

	list_del_rcu(&phyinfo->node);
	synchronize_rcu();

	/* Fail if reference count is not zero */
	if (cffrml_refcnt_read(phyinfo->frm_layer) != 0) {
		pr_info("Wait for device inuse\n");
		list_add_rcu(&phyinfo->node, &cnfg->phys);
		mutex_unlock(&cnfg->lock);
		return -EAGAIN;
	}

	frml = phyinfo->frm_layer;
	frml_dn = frml->dn;
	cffrml_set_uplayer(frml, NULL);
	cffrml_set_dnlayer(frml, NULL);
	if (phy_layer != frml_dn) {
		layer_set_up(frml_dn, NULL);
		layer_set_dn(frml_dn, NULL);
	}
	layer_set_up(phy_layer, NULL);

	if (phyinfo->phy_layer != frml_dn)
		kfree(frml_dn);

	cffrml_free(frml);
	kfree(phyinfo);
	mutex_unlock(&cnfg->lock);

	return 0;
}