#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ relkind; scalar_t__ relpersistence; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* Form_pg_class ;

/* Variables and functions */
 scalar_t__ FirstNormalObjectId ; 
 int /*<<< orphan*/  IsCatalogRelationOid (scalar_t__) ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELPERSISTENCE_PERMANENT ; 

__attribute__((used)) static bool
is_publishable_class(Oid relid, Form_pg_class reltuple)
{
	return reltuple->relkind == RELKIND_RELATION &&
		!IsCatalogRelationOid(relid) &&
		reltuple->relpersistence == RELPERSISTENCE_PERMANENT &&
		relid >= FirstNormalObjectId;
}