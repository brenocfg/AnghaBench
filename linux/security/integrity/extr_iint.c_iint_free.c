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
struct integrity_iint_cache {unsigned long flags; unsigned long atomic_flags; scalar_t__ measured_pcrs; void* evm_status; void* ima_creds_status; void* ima_read_status; void* ima_bprm_status; void* ima_mmap_status; void* ima_file_status; scalar_t__ version; int /*<<< orphan*/ * ima_hash; } ;

/* Variables and functions */
 void* INTEGRITY_UNKNOWN ; 
 int /*<<< orphan*/  iint_cache ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct integrity_iint_cache*) ; 

__attribute__((used)) static void iint_free(struct integrity_iint_cache *iint)
{
	kfree(iint->ima_hash);
	iint->ima_hash = NULL;
	iint->version = 0;
	iint->flags = 0UL;
	iint->atomic_flags = 0UL;
	iint->ima_file_status = INTEGRITY_UNKNOWN;
	iint->ima_mmap_status = INTEGRITY_UNKNOWN;
	iint->ima_bprm_status = INTEGRITY_UNKNOWN;
	iint->ima_read_status = INTEGRITY_UNKNOWN;
	iint->ima_creds_status = INTEGRITY_UNKNOWN;
	iint->evm_status = INTEGRITY_UNKNOWN;
	iint->measured_pcrs = 0;
	kmem_cache_free(iint_cache, iint);
}