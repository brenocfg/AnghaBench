#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* fn_oid; } ;
struct TYPE_6__ {int valid; TYPE_4__ cast_func_finfo; TYPE_4__ eq_opr_finfo; } ;
struct TYPE_5__ {scalar_t__ typeid; scalar_t__ eq_opr; } ;
typedef  TYPE_1__ RI_CompareKey ;
typedef  TYPE_2__ RI_CompareHashEntry ;
typedef  scalar_t__ Oid ;
typedef  scalar_t__ CoercionPathType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COERCION_IMPLICIT ; 
 scalar_t__ COERCION_PATH_FUNC ; 
 scalar_t__ COERCION_PATH_RELABELTYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  IsBinaryCoercible (scalar_t__,scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_coercion_pathway (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  fmgr_info_cxt (scalar_t__,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_opcode (scalar_t__) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  op_input_types (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ri_InitHashTables () ; 
 int /*<<< orphan*/  ri_compare_cache ; 

__attribute__((used)) static RI_CompareHashEntry *
ri_HashCompareOp(Oid eq_opr, Oid typeid)
{
	RI_CompareKey key;
	RI_CompareHashEntry *entry;
	bool		found;

	/*
	 * On the first call initialize the hashtable
	 */
	if (!ri_compare_cache)
		ri_InitHashTables();

	/*
	 * Find or create a hash entry.  Note we're assuming RI_CompareKey
	 * contains no struct padding.
	 */
	key.eq_opr = eq_opr;
	key.typeid = typeid;
	entry = (RI_CompareHashEntry *) hash_search(ri_compare_cache,
												(void *) &key,
												HASH_ENTER, &found);
	if (!found)
		entry->valid = false;

	/*
	 * If not already initialized, do so.  Since we'll keep this hash entry
	 * for the life of the backend, put any subsidiary info for the function
	 * cache structs into TopMemoryContext.
	 */
	if (!entry->valid)
	{
		Oid			lefttype,
					righttype,
					castfunc;
		CoercionPathType pathtype;

		/* We always need to know how to call the equality operator */
		fmgr_info_cxt(get_opcode(eq_opr), &entry->eq_opr_finfo,
					  TopMemoryContext);

		/*
		 * If we chose to use a cast from FK to PK type, we may have to apply
		 * the cast function to get to the operator's input type.
		 *
		 * XXX eventually it would be good to support array-coercion cases
		 * here and in ri_AttributesEqual().  At the moment there is no point
		 * because cases involving nonidentical array types will be rejected
		 * at constraint creation time.
		 *
		 * XXX perhaps also consider supporting CoerceViaIO?  No need at the
		 * moment since that will never be generated for implicit coercions.
		 */
		op_input_types(eq_opr, &lefttype, &righttype);
		Assert(lefttype == righttype);
		if (typeid == lefttype)
			castfunc = InvalidOid;	/* simplest case */
		else
		{
			pathtype = find_coercion_pathway(lefttype, typeid,
											 COERCION_IMPLICIT,
											 &castfunc);
			if (pathtype != COERCION_PATH_FUNC &&
				pathtype != COERCION_PATH_RELABELTYPE)
			{
				/*
				 * The declared input type of the eq_opr might be a
				 * polymorphic type such as ANYARRAY or ANYENUM, or other
				 * special cases such as RECORD; find_coercion_pathway
				 * currently doesn't subsume these special cases.
				 */
				if (!IsBinaryCoercible(typeid, lefttype))
					elog(ERROR, "no conversion function from %s to %s",
						 format_type_be(typeid),
						 format_type_be(lefttype));
			}
		}
		if (OidIsValid(castfunc))
			fmgr_info_cxt(castfunc, &entry->cast_func_finfo,
						  TopMemoryContext);
		else
			entry->cast_func_finfo.fn_oid = InvalidOid;
		entry->valid = true;
	}

	return entry;
}