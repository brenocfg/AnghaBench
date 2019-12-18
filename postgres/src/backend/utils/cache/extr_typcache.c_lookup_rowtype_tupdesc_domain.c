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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {scalar_t__ typtype; int /*<<< orphan*/ * tupDesc; int /*<<< orphan*/  domainBaseTypmod; int /*<<< orphan*/  domainBaseType; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PinTupleDesc (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORDOID ; 
 int TYPECACHE_DOMAIN_BASE_INFO ; 
 int TYPECACHE_TUPDESC ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 int /*<<< orphan*/ * lookup_rowtype_tupdesc_internal (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lookup_rowtype_tupdesc_noerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* lookup_type_cache (scalar_t__,int) ; 

TupleDesc
lookup_rowtype_tupdesc_domain(Oid type_id, int32 typmod, bool noError)
{
	TupleDesc	tupDesc;

	if (type_id != RECORDOID)
	{
		/*
		 * Check for domain or named composite type.  We might as well load
		 * whichever data is needed.
		 */
		TypeCacheEntry *typentry;

		typentry = lookup_type_cache(type_id,
									 TYPECACHE_TUPDESC |
									 TYPECACHE_DOMAIN_BASE_INFO);
		if (typentry->typtype == TYPTYPE_DOMAIN)
			return lookup_rowtype_tupdesc_noerror(typentry->domainBaseType,
												  typentry->domainBaseTypmod,
												  noError);
		if (typentry->tupDesc == NULL && !noError)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("type %s is not composite",
							format_type_be(type_id))));
		tupDesc = typentry->tupDesc;
	}
	else
		tupDesc = lookup_rowtype_tupdesc_internal(type_id, typmod, noError);
	if (tupDesc != NULL)
		PinTupleDesc(tupDesc);
	return tupDesc;
}