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
typedef  size_t uint32_t ;
struct dlm_rsb {size_t res_bucket; int /*<<< orphan*/  res_ref; struct dlm_ls* res_ls; } ;
struct dlm_ls {TYPE_1__* ls_rsbtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toss_rsb ; 

__attribute__((used)) static void put_rsb(struct dlm_rsb *r)
{
	struct dlm_ls *ls = r->res_ls;
	uint32_t bucket = r->res_bucket;

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	kref_put(&r->res_ref, toss_rsb);
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);
}