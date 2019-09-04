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
struct dlm_ctxt {struct dlm_ctxt* name; scalar_t__ master_hash; scalar_t__ lockres_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_HASH_PAGES ; 
 int /*<<< orphan*/  dlm_destroy_debugfs_subroot (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_free_pagevec (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dlm_ctxt*) ; 

__attribute__((used)) static void dlm_free_ctxt_mem(struct dlm_ctxt *dlm)
{
	dlm_destroy_debugfs_subroot(dlm);

	if (dlm->lockres_hash)
		dlm_free_pagevec((void **)dlm->lockres_hash, DLM_HASH_PAGES);

	if (dlm->master_hash)
		dlm_free_pagevec((void **)dlm->master_hash, DLM_HASH_PAGES);

	kfree(dlm->name);
	kfree(dlm);
}