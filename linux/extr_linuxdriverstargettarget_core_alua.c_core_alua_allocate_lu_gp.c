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
struct t10_alua_lu_gp {int lu_gp_valid_id; scalar_t__ lu_gp_id; int /*<<< orphan*/  lu_gp_ref_cnt; int /*<<< orphan*/  lu_gp_lock; int /*<<< orphan*/  lu_gp_mem_list; int /*<<< orphan*/  lu_gp_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct t10_alua_lu_gp* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alua_lu_gps_count ; 
 int /*<<< orphan*/  alua_lu_gps_counter ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct t10_alua_lu_gp* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t10_alua_lu_gp_cache ; 

struct t10_alua_lu_gp *
core_alua_allocate_lu_gp(const char *name, int def_group)
{
	struct t10_alua_lu_gp *lu_gp;

	lu_gp = kmem_cache_zalloc(t10_alua_lu_gp_cache, GFP_KERNEL);
	if (!lu_gp) {
		pr_err("Unable to allocate struct t10_alua_lu_gp\n");
		return ERR_PTR(-ENOMEM);
	}
	INIT_LIST_HEAD(&lu_gp->lu_gp_node);
	INIT_LIST_HEAD(&lu_gp->lu_gp_mem_list);
	spin_lock_init(&lu_gp->lu_gp_lock);
	atomic_set(&lu_gp->lu_gp_ref_cnt, 0);

	if (def_group) {
		lu_gp->lu_gp_id = alua_lu_gps_counter++;
		lu_gp->lu_gp_valid_id = 1;
		alua_lu_gps_count++;
	}

	return lu_gp;
}