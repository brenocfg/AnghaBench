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
struct TYPE_2__ {void* name; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dlm_init_lockres (struct dlm_ctxt*,struct dlm_lock_resource*,char const*,unsigned int) ; 
 int /*<<< orphan*/  dlm_lockname_cache ; 
 int /*<<< orphan*/  dlm_lockres_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dlm_lock_resource*) ; 
 void* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dlm_lock_resource *dlm_new_lockres(struct dlm_ctxt *dlm,
				   const char *name,
				   unsigned int namelen)
{
	struct dlm_lock_resource *res = NULL;

	res = kmem_cache_zalloc(dlm_lockres_cache, GFP_NOFS);
	if (!res)
		goto error;

	res->lockname.name = kmem_cache_zalloc(dlm_lockname_cache, GFP_NOFS);
	if (!res->lockname.name)
		goto error;

	dlm_init_lockres(dlm, res, name, namelen);
	return res;

error:
	if (res)
		kmem_cache_free(dlm_lockres_cache, res);
	return NULL;
}