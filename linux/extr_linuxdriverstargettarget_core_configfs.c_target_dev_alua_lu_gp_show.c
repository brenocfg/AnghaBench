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
struct t10_alua_lu_gp_member {int /*<<< orphan*/  lu_gp_mem_lock; struct t10_alua_lu_gp* lu_gp; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {struct config_item cg_item; } ;
struct t10_alua_lu_gp {int /*<<< orphan*/  lu_gp_id; TYPE_1__ lu_gp_group; } ;
struct se_device {struct t10_alua_lu_gp_member* dev_alua_lu_gp_mem; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* config_item_name (struct config_item*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 struct se_device* to_device (struct config_item*) ; 

__attribute__((used)) static ssize_t target_dev_alua_lu_gp_show(struct config_item *item, char *page)
{
	struct se_device *dev = to_device(item);
	struct config_item *lu_ci;
	struct t10_alua_lu_gp *lu_gp;
	struct t10_alua_lu_gp_member *lu_gp_mem;
	ssize_t len = 0;

	lu_gp_mem = dev->dev_alua_lu_gp_mem;
	if (!lu_gp_mem)
		return 0;

	spin_lock(&lu_gp_mem->lu_gp_mem_lock);
	lu_gp = lu_gp_mem->lu_gp;
	if (lu_gp) {
		lu_ci = &lu_gp->lu_gp_group.cg_item;
		len += sprintf(page, "LU Group Alias: %s\nLU Group ID: %hu\n",
			config_item_name(lu_ci), lu_gp->lu_gp_id);
	}
	spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

	return len;
}