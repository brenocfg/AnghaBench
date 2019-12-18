#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_22__ {char typtype; int typbyval; int typlen; char typalign; int domainBaseType; int typelem; int /*<<< orphan*/  domainBaseTypmod; } ;
typedef  TYPE_8__ TypeCacheEntry ;
struct TYPE_23__ {int /*<<< orphan*/  trftypes; int /*<<< orphan*/  langid; } ;
struct TYPE_20__ {int /*<<< orphan*/  typfunc; int /*<<< orphan*/  typioparam; } ;
struct TYPE_18__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_19__ {TYPE_4__ recinfunc; scalar_t__ natts; int /*<<< orphan*/ * atts; int /*<<< orphan*/  tupdescid; TYPE_8__* typentry; int /*<<< orphan*/ * recdesc; } ;
struct TYPE_17__ {int /*<<< orphan*/  typtransform; } ;
struct TYPE_16__ {TYPE_10__* elm; int /*<<< orphan*/  elmbasetype; } ;
struct TYPE_15__ {TYPE_10__* base; int /*<<< orphan*/ * domain_info; } ;
struct TYPE_21__ {TYPE_6__ scalar; TYPE_5__ tuple; TYPE_3__ transform; TYPE_2__ array; TYPE_1__ domain; } ;
struct TYPE_14__ {int typoid; int typbyval; int typlen; char typalign; TYPE_7__ u; int /*<<< orphan*/  func; int /*<<< orphan*/  mcxt; int /*<<< orphan*/  typmod; } ;
typedef  TYPE_9__ PLyProcedure ;
typedef  TYPE_10__ PLyObToDatum ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
#define  BOOLOID 129 
#define  BYTEAOID 128 
 int /*<<< orphan*/  INVALID_TUPLEDESC_IDENTIFIER ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OidIsValid (int) ; 
 int /*<<< orphan*/  PLyObject_ToBool ; 
 int /*<<< orphan*/  PLyObject_ToBytea ; 
 int /*<<< orphan*/  PLyObject_ToComposite ; 
 int /*<<< orphan*/  PLyObject_ToDomain ; 
 int /*<<< orphan*/  PLyObject_ToScalar ; 
 int /*<<< orphan*/  PLyObject_ToTransform ; 
 int /*<<< orphan*/  PLySequence_ToArray ; 
 int RECORDOID ; 
 int /*<<< orphan*/  TYPECACHE_DOMAIN_BASE_INFO ; 
 char TYPTYPE_COMPOSITE ; 
 char TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  fmgr_info_cxt (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getBaseType (int) ; 
 int /*<<< orphan*/  getTypeInputInfo (int,int*,int /*<<< orphan*/ *) ; 
 int get_transform_tosql (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* lookup_type_cache (int,int /*<<< orphan*/ ) ; 

void
PLy_output_setup_func(PLyObToDatum *arg, MemoryContext arg_mcxt,
					  Oid typeOid, int32 typmod,
					  PLyProcedure *proc)
{
	TypeCacheEntry *typentry;
	char		typtype;
	Oid			trfuncid;
	Oid			typinput;

	/* Since this is recursive, it could theoretically be driven to overflow */
	check_stack_depth();

	arg->typoid = typeOid;
	arg->typmod = typmod;
	arg->mcxt = arg_mcxt;

	/*
	 * Fetch typcache entry for the target type, asking for whatever info
	 * we'll need later.  RECORD is a special case: just treat it as composite
	 * without bothering with the typcache entry.
	 */
	if (typeOid != RECORDOID)
	{
		typentry = lookup_type_cache(typeOid, TYPECACHE_DOMAIN_BASE_INFO);
		typtype = typentry->typtype;
		arg->typbyval = typentry->typbyval;
		arg->typlen = typentry->typlen;
		arg->typalign = typentry->typalign;
	}
	else
	{
		typentry = NULL;
		typtype = TYPTYPE_COMPOSITE;
		/* hard-wired knowledge about type RECORD: */
		arg->typbyval = false;
		arg->typlen = -1;
		arg->typalign = 'd';
	}

	/*
	 * Choose conversion method.  Note that transform functions are checked
	 * for composite and scalar types, but not for arrays or domains.  This is
	 * somewhat historical, but we'd have a problem allowing them on domains,
	 * since we drill down through all levels of a domain nest without looking
	 * at the intermediate levels at all.
	 */
	if (typtype == TYPTYPE_DOMAIN)
	{
		/* Domain */
		arg->func = PLyObject_ToDomain;
		arg->u.domain.domain_info = NULL;
		/* Recursively set up conversion info for the element type */
		arg->u.domain.base = (PLyObToDatum *)
			MemoryContextAllocZero(arg_mcxt, sizeof(PLyObToDatum));
		PLy_output_setup_func(arg->u.domain.base, arg_mcxt,
							  typentry->domainBaseType,
							  typentry->domainBaseTypmod,
							  proc);
	}
	else if (typentry &&
			 OidIsValid(typentry->typelem) && typentry->typlen == -1)
	{
		/* Standard varlena array (cf. get_element_type) */
		arg->func = PLySequence_ToArray;
		/* Get base type OID to insert into constructed array */
		/* (note this might not be the same as the immediate child type) */
		arg->u.array.elmbasetype = getBaseType(typentry->typelem);
		/* Recursively set up conversion info for the element type */
		arg->u.array.elm = (PLyObToDatum *)
			MemoryContextAllocZero(arg_mcxt, sizeof(PLyObToDatum));
		PLy_output_setup_func(arg->u.array.elm, arg_mcxt,
							  typentry->typelem, typmod,
							  proc);
	}
	else if ((trfuncid = get_transform_tosql(typeOid,
											 proc->langid,
											 proc->trftypes)))
	{
		arg->func = PLyObject_ToTransform;
		fmgr_info_cxt(trfuncid, &arg->u.transform.typtransform, arg_mcxt);
	}
	else if (typtype == TYPTYPE_COMPOSITE)
	{
		/* Named composite type, or RECORD */
		arg->func = PLyObject_ToComposite;
		/* We'll set up the per-field data later */
		arg->u.tuple.recdesc = NULL;
		arg->u.tuple.typentry = typentry;
		arg->u.tuple.tupdescid = INVALID_TUPLEDESC_IDENTIFIER;
		arg->u.tuple.atts = NULL;
		arg->u.tuple.natts = 0;
		/* Mark this invalid till needed, too */
		arg->u.tuple.recinfunc.fn_oid = InvalidOid;
	}
	else
	{
		/* Scalar type, but we have a couple of special cases */
		switch (typeOid)
		{
			case BOOLOID:
				arg->func = PLyObject_ToBool;
				break;
			case BYTEAOID:
				arg->func = PLyObject_ToBytea;
				break;
			default:
				arg->func = PLyObject_ToScalar;
				getTypeInputInfo(typeOid, &typinput, &arg->u.scalar.typioparam);
				fmgr_info_cxt(typinput, &arg->u.scalar.typfunc, arg_mcxt);
				break;
		}
	}
}