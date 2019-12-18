#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ typtype; scalar_t__ domainData; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_9__ {int /*<<< orphan*/  constraints; int /*<<< orphan*/  dccRefCount; } ;
struct TYPE_8__ {scalar_t__ dcc; int /*<<< orphan*/  constraints; int /*<<< orphan*/  refctx; scalar_t__ need_exprstate; TYPE_1__* tcache; } ;
typedef  TYPE_2__ DomainConstraintRef ;
typedef  TYPE_3__ DomainConstraintCache ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int TCFLAGS_CHECKED_DOMAIN_CONSTRAINTS ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  decr_dcc_refcount (TYPE_3__*) ; 
 int /*<<< orphan*/  load_domaintype_info (TYPE_1__*) ; 
 int /*<<< orphan*/  prep_domain_constraints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
UpdateDomainConstraintRef(DomainConstraintRef *ref)
{
	TypeCacheEntry *typentry = ref->tcache;

	/* Make sure typcache entry's data is up to date */
	if ((typentry->flags & TCFLAGS_CHECKED_DOMAIN_CONSTRAINTS) == 0 &&
		typentry->typtype == TYPTYPE_DOMAIN)
		load_domaintype_info(typentry);

	/* Transfer to ref object if there's new info, adjusting refcounts */
	if (ref->dcc != typentry->domainData)
	{
		/* Paranoia --- be sure link is nulled before trying to release */
		DomainConstraintCache *dcc = ref->dcc;

		if (dcc)
		{
			/*
			 * Note: we just leak the previous list of executable domain
			 * constraints.  Alternatively, we could keep those in a child
			 * context of ref->refctx and free that context at this point.
			 * However, in practice this code path will be taken so seldom
			 * that the extra bookkeeping for a child context doesn't seem
			 * worthwhile; we'll just allow a leak for the lifespan of refctx.
			 */
			ref->constraints = NIL;
			ref->dcc = NULL;
			decr_dcc_refcount(dcc);
		}
		dcc = typentry->domainData;
		if (dcc)
		{
			ref->dcc = dcc;
			dcc->dccRefCount++;
			if (ref->need_exprstate)
				ref->constraints = prep_domain_constraints(dcc->constraints,
														   ref->refctx);
			else
				ref->constraints = dcc->constraints;
		}
	}
}