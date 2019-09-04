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
typedef  scalar_t__ uint64_t ;
struct dlm_rsb {int dummy; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recover_idr_lock; int /*<<< orphan*/  ls_recover_idr; } ;

/* Variables and functions */
 struct dlm_rsb* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dlm_rsb *recover_idr_find(struct dlm_ls *ls, uint64_t id)
{
	struct dlm_rsb *r;

	spin_lock(&ls->ls_recover_idr_lock);
	r = idr_find(&ls->ls_recover_idr, (int)id);
	spin_unlock(&ls->ls_recover_idr_lock);
	return r;
}