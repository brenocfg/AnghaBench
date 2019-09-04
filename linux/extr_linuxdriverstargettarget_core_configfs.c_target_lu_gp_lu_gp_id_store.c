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
typedef  int /*<<< orphan*/  u16 ;
struct config_group {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_lu_gp {int /*<<< orphan*/  lu_gp_id; struct config_group lu_gp_group; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int core_alua_set_lu_gp_id (struct t10_alua_lu_gp*,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 struct t10_alua_lu_gp* to_lu_gp (struct config_item*) ; 

__attribute__((used)) static ssize_t target_lu_gp_lu_gp_id_store(struct config_item *item,
		const char *page, size_t count)
{
	struct t10_alua_lu_gp *lu_gp = to_lu_gp(item);
	struct config_group *alua_lu_gp_cg = &lu_gp->lu_gp_group;
	unsigned long lu_gp_id;
	int ret;

	ret = kstrtoul(page, 0, &lu_gp_id);
	if (ret < 0) {
		pr_err("kstrtoul() returned %d for"
			" lu_gp_id\n", ret);
		return ret;
	}
	if (lu_gp_id > 0x0000ffff) {
		pr_err("ALUA lu_gp_id: %lu exceeds maximum:"
			" 0x0000ffff\n", lu_gp_id);
		return -EINVAL;
	}

	ret = core_alua_set_lu_gp_id(lu_gp, (u16)lu_gp_id);
	if (ret < 0)
		return -EINVAL;

	pr_debug("Target_Core_ConfigFS: Set ALUA Logical Unit"
		" Group: core/alua/lu_gps/%s to ID: %hu\n",
		config_item_name(&alua_lu_gp_cg->cg_item),
		lu_gp->lu_gp_id);

	return count;
}