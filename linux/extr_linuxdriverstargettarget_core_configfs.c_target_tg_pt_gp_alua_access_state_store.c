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
struct t10_alua_tg_pt_gp {int tg_pt_gp_alua_access_type; int /*<<< orphan*/  tg_pt_gp_valid_id; struct se_device* tg_pt_gp_dev; } ;
struct se_device {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ALUA_ACCESS_STATE_LBA_DEPENDENT ; 
 int EINVAL ; 
 int ENODEV ; 
 int TPGS_EXPLICIT_ALUA ; 
 int TPGS_IMPLICIT_ALUA ; 
 int core_alua_do_port_transition (struct t10_alua_tg_pt_gp*,struct se_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  target_dev_configured (struct se_device*) ; 
 struct t10_alua_tg_pt_gp* to_tg_pt_gp (struct config_item*) ; 

__attribute__((used)) static ssize_t target_tg_pt_gp_alua_access_state_store(struct config_item *item,
		const char *page, size_t count)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	struct se_device *dev = tg_pt_gp->tg_pt_gp_dev;
	unsigned long tmp;
	int new_state, ret;

	if (!tg_pt_gp->tg_pt_gp_valid_id) {
		pr_err("Unable to do implicit ALUA on non valid"
			" tg_pt_gp ID: %hu\n", tg_pt_gp->tg_pt_gp_valid_id);
		return -EINVAL;
	}
	if (!target_dev_configured(dev)) {
		pr_err("Unable to set alua_access_state while device is"
		       " not configured\n");
		return -ENODEV;
	}

	ret = kstrtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract new ALUA access state from"
				" %s\n", page);
		return ret;
	}
	new_state = (int)tmp;

	if (!(tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_IMPLICIT_ALUA)) {
		pr_err("Unable to process implicit configfs ALUA"
			" transition while TPGS_IMPLICIT_ALUA is disabled\n");
		return -EINVAL;
	}
	if (tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_EXPLICIT_ALUA &&
	    new_state == ALUA_ACCESS_STATE_LBA_DEPENDENT) {
		/* LBA DEPENDENT is only allowed with implicit ALUA */
		pr_err("Unable to process implicit configfs ALUA transition"
		       " while explicit ALUA management is enabled\n");
		return -EINVAL;
	}

	ret = core_alua_do_port_transition(tg_pt_gp, dev,
					NULL, NULL, new_state, 0);
	return (!ret) ? count : -EINVAL;
}