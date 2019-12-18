#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* arg; int /*<<< orphan*/  func; } ;
struct TYPE_8__ {TYPE_1__* domainData; } ;
struct TYPE_7__ {int need_exprstate; int /*<<< orphan*/  constraints; TYPE_1__* dcc; int /*<<< orphan*/  refctx; TYPE_3__* tcache; TYPE_4__ callback; } ;
struct TYPE_6__ {int /*<<< orphan*/  constraints; int /*<<< orphan*/  dccRefCount; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ DomainConstraintRef ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextRegisterResetCallback (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  TYPECACHE_DOMAIN_CONSTR_INFO ; 
 int /*<<< orphan*/  dccref_deletion_callback ; 
 TYPE_3__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_domain_constraints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
InitDomainConstraintRef(Oid type_id, DomainConstraintRef *ref,
						MemoryContext refctx, bool need_exprstate)
{
	/* Look up the typcache entry --- we assume it survives indefinitely */
	ref->tcache = lookup_type_cache(type_id, TYPECACHE_DOMAIN_CONSTR_INFO);
	ref->need_exprstate = need_exprstate;
	/* For safety, establish the callback before acquiring a refcount */
	ref->refctx = refctx;
	ref->dcc = NULL;
	ref->callback.func = dccref_deletion_callback;
	ref->callback.arg = (void *) ref;
	MemoryContextRegisterResetCallback(refctx, &ref->callback);
	/* Acquire refcount if there are constraints, and set up exported list */
	if (ref->tcache->domainData)
	{
		ref->dcc = ref->tcache->domainData;
		ref->dcc->dccRefCount++;
		if (ref->need_exprstate)
			ref->constraints = prep_domain_constraints(ref->dcc->constraints,
													   ref->refctx);
		else
			ref->constraints = ref->dcc->constraints;
	}
	else
		ref->constraints = NIL;
}