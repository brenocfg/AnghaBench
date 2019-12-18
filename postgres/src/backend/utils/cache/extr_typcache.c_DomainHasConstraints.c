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
struct TYPE_3__ {int /*<<< orphan*/ * domainData; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  TYPECACHE_DOMAIN_CONSTR_INFO ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
DomainHasConstraints(Oid type_id)
{
	TypeCacheEntry *typentry;

	/*
	 * Note: a side effect is to cause the typcache's domain data to become
	 * valid.  This is fine since we'll likely need it soon if there is any.
	 */
	typentry = lookup_type_cache(type_id, TYPECACHE_DOMAIN_CONSTR_INFO);

	return (typentry->domainData != NULL);
}