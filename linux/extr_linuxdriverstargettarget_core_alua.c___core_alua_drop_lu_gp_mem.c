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
struct t10_alua_lu_gp_member {scalar_t__ lu_gp_assoc; int /*<<< orphan*/ * lu_gp; int /*<<< orphan*/  lu_gp_mem_list; } ;
struct t10_alua_lu_gp {int /*<<< orphan*/  lu_gp_lock; int /*<<< orphan*/  lu_gp_members; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __core_alua_drop_lu_gp_mem(
	struct t10_alua_lu_gp_member *lu_gp_mem,
	struct t10_alua_lu_gp *lu_gp)
{
	spin_lock(&lu_gp->lu_gp_lock);
	list_del(&lu_gp_mem->lu_gp_mem_list);
	lu_gp_mem->lu_gp = NULL;
	lu_gp_mem->lu_gp_assoc = 0;
	lu_gp->lu_gp_members--;
	spin_unlock(&lu_gp->lu_gp_lock);
}