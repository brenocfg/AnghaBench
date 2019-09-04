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
struct t10_alua_tg_pt_gp {int tg_pt_gp_alua_access_type; int tg_pt_gp_alua_supported_states; int tg_pt_gp_valid_id; int /*<<< orphan*/  tg_pt_gp_list; scalar_t__ tg_pt_gp_id; int /*<<< orphan*/  tg_pt_gp_implicit_trans_secs; int /*<<< orphan*/  tg_pt_gp_trans_delay_msecs; int /*<<< orphan*/  tg_pt_gp_nonop_delay_msecs; int /*<<< orphan*/  tg_pt_gp_alua_access_state; struct se_device* tg_pt_gp_dev; int /*<<< orphan*/  tg_pt_gp_ref_cnt; int /*<<< orphan*/  tg_pt_gp_lock; int /*<<< orphan*/  tg_pt_gp_transition_mutex; int /*<<< orphan*/  tg_pt_gp_lun_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  tg_pt_gps_lock; int /*<<< orphan*/  tg_pt_gps_list; int /*<<< orphan*/  alua_tg_pt_gps_count; int /*<<< orphan*/  alua_tg_pt_gps_counter; } ;
struct se_device {TYPE_1__ t10_alua; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED ; 
 int ALUA_AN_SUP ; 
 int ALUA_AO_SUP ; 
 int /*<<< orphan*/  ALUA_DEFAULT_IMPLICIT_TRANS_SECS ; 
 int /*<<< orphan*/  ALUA_DEFAULT_NONOP_DELAY_MSECS ; 
 int /*<<< orphan*/  ALUA_DEFAULT_TRANS_DELAY_MSECS ; 
 int ALUA_O_SUP ; 
 int ALUA_S_SUP ; 
 int ALUA_T_SUP ; 
 int ALUA_U_SUP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TPGS_EXPLICIT_ALUA ; 
 int TPGS_IMPLICIT_ALUA ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct t10_alua_tg_pt_gp* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t10_alua_tg_pt_gp_cache ; 

struct t10_alua_tg_pt_gp *core_alua_allocate_tg_pt_gp(struct se_device *dev,
		const char *name, int def_group)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp;

	tg_pt_gp = kmem_cache_zalloc(t10_alua_tg_pt_gp_cache, GFP_KERNEL);
	if (!tg_pt_gp) {
		pr_err("Unable to allocate struct t10_alua_tg_pt_gp\n");
		return NULL;
	}
	INIT_LIST_HEAD(&tg_pt_gp->tg_pt_gp_list);
	INIT_LIST_HEAD(&tg_pt_gp->tg_pt_gp_lun_list);
	mutex_init(&tg_pt_gp->tg_pt_gp_transition_mutex);
	spin_lock_init(&tg_pt_gp->tg_pt_gp_lock);
	atomic_set(&tg_pt_gp->tg_pt_gp_ref_cnt, 0);
	tg_pt_gp->tg_pt_gp_dev = dev;
	tg_pt_gp->tg_pt_gp_alua_access_state =
			ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED;
	/*
	 * Enable both explicit and implicit ALUA support by default
	 */
	tg_pt_gp->tg_pt_gp_alua_access_type =
			TPGS_EXPLICIT_ALUA | TPGS_IMPLICIT_ALUA;
	/*
	 * Set the default Active/NonOptimized Delay in milliseconds
	 */
	tg_pt_gp->tg_pt_gp_nonop_delay_msecs = ALUA_DEFAULT_NONOP_DELAY_MSECS;
	tg_pt_gp->tg_pt_gp_trans_delay_msecs = ALUA_DEFAULT_TRANS_DELAY_MSECS;
	tg_pt_gp->tg_pt_gp_implicit_trans_secs = ALUA_DEFAULT_IMPLICIT_TRANS_SECS;

	/*
	 * Enable all supported states
	 */
	tg_pt_gp->tg_pt_gp_alua_supported_states =
	    ALUA_T_SUP | ALUA_O_SUP |
	    ALUA_U_SUP | ALUA_S_SUP | ALUA_AN_SUP | ALUA_AO_SUP;

	if (def_group) {
		spin_lock(&dev->t10_alua.tg_pt_gps_lock);
		tg_pt_gp->tg_pt_gp_id =
				dev->t10_alua.alua_tg_pt_gps_counter++;
		tg_pt_gp->tg_pt_gp_valid_id = 1;
		dev->t10_alua.alua_tg_pt_gps_count++;
		list_add_tail(&tg_pt_gp->tg_pt_gp_list,
			      &dev->t10_alua.tg_pt_gps_list);
		spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
	}

	return tg_pt_gp;
}