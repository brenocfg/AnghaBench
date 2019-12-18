#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tupDesc_identifier; scalar_t__ typtype; int /*<<< orphan*/ * tupDesc; int /*<<< orphan*/  domainBaseType; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_8__ {int /*<<< orphan*/  rectypeid; TYPE_2__* datatype; } ;
struct TYPE_7__ {scalar_t__ tupdesc_id; int /*<<< orphan*/  typoid; TYPE_1__* tcache; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/ * origtypname; } ;
typedef  TYPE_2__ PLpgSQL_type ;
typedef  TYPE_3__ PLpgSQL_rec ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RECORDOID ; 
 int TYPECACHE_DOMAIN_BASE_INFO ; 
 int TYPECACHE_TUPDESC ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  typenameTypeIdAndMod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
revalidate_rectypeid(PLpgSQL_rec *rec)
{
	PLpgSQL_type *typ = rec->datatype;
	TypeCacheEntry *typentry;

	if (rec->rectypeid == RECORDOID)
		return;					/* it's RECORD, so nothing to do */
	Assert(typ != NULL);
	if (typ->tcache &&
		typ->tcache->tupDesc_identifier == typ->tupdesc_id)
		return;					/* known up-to-date */

	/*
	 * typcache entry has suffered invalidation, so re-look-up the type name
	 * if possible, and then recheck the type OID.  If we don't have a
	 * TypeName, then we just have to soldier on with the OID we've got.
	 */
	if (typ->origtypname != NULL)
	{
		/* this bit should match parse_datatype() in pl_gram.y */
		typenameTypeIdAndMod(NULL, typ->origtypname,
							 &typ->typoid,
							 &typ->atttypmod);
	}

	/* this bit should match build_datatype() in pl_comp.c */
	typentry = lookup_type_cache(typ->typoid,
								 TYPECACHE_TUPDESC |
								 TYPECACHE_DOMAIN_BASE_INFO);
	if (typentry->typtype == TYPTYPE_DOMAIN)
		typentry = lookup_type_cache(typentry->domainBaseType,
									 TYPECACHE_TUPDESC);
	if (typentry->tupDesc == NULL)
	{
		/*
		 * If we get here, user tried to replace a composite type with a
		 * non-composite one.  We're not gonna support that.
		 */
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("type %s is not composite",
						format_type_be(typ->typoid))));
	}

	/*
	 * Update tcache and tupdesc_id.  Since we don't support changing to a
	 * non-composite type, none of the rest of *typ needs to change.
	 */
	typ->tcache = typentry;
	typ->tupdesc_id = typentry->tupDesc_identifier;

	/*
	 * Update *rec, too.  (We'll deal with subsidiary RECFIELDs as needed.)
	 */
	rec->rectypeid = typ->typoid;
}