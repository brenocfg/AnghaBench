#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_17__ {char typtype; int typbyval; int typlen; char typalign; int domainBaseType; int typelem; int /*<<< orphan*/  domainBaseTypmod; } ;
typedef  TYPE_6__ TypeCacheEntry ;
struct TYPE_15__ {int /*<<< orphan*/  typfunc; } ;
struct TYPE_14__ {scalar_t__ natts; int /*<<< orphan*/ * atts; int /*<<< orphan*/  tupdescid; TYPE_6__* typentry; int /*<<< orphan*/ * recdesc; } ;
struct TYPE_13__ {int /*<<< orphan*/  typtransform; } ;
struct TYPE_12__ {TYPE_8__* elm; } ;
struct TYPE_16__ {TYPE_4__ scalar; TYPE_3__ tuple; TYPE_2__ transform; TYPE_1__ array; } ;
struct TYPE_19__ {int typoid; int typbyval; int typlen; char typalign; TYPE_5__ u; int /*<<< orphan*/  func; int /*<<< orphan*/  mcxt; int /*<<< orphan*/  typmod; } ;
struct TYPE_18__ {int /*<<< orphan*/  trftypes; int /*<<< orphan*/  langid; } ;
typedef  TYPE_7__ PLyProcedure ;
typedef  TYPE_8__ PLyDatumToOb ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
#define  BOOLOID 136 
#define  BYTEAOID 135 
#define  FLOAT4OID 134 
#define  FLOAT8OID 133 
#define  INT2OID 132 
#define  INT4OID 131 
#define  INT8OID 130 
 int /*<<< orphan*/  INVALID_TUPLEDESC_IDENTIFIER ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
#define  NUMERICOID 129 
#define  OIDOID 128 
 scalar_t__ OidIsValid (int) ; 
 int /*<<< orphan*/  PLyBool_FromBool ; 
 int /*<<< orphan*/  PLyBytes_FromBytea ; 
 int /*<<< orphan*/  PLyDecimal_FromNumeric ; 
 int /*<<< orphan*/  PLyDict_FromComposite ; 
 int /*<<< orphan*/  PLyFloat_FromFloat4 ; 
 int /*<<< orphan*/  PLyFloat_FromFloat8 ; 
 int /*<<< orphan*/  PLyInt_FromInt16 ; 
 int /*<<< orphan*/  PLyInt_FromInt32 ; 
 int /*<<< orphan*/  PLyList_FromArray ; 
 int /*<<< orphan*/  PLyLong_FromInt64 ; 
 int /*<<< orphan*/  PLyLong_FromOid ; 
 int /*<<< orphan*/  PLyObject_FromTransform ; 
 int /*<<< orphan*/  PLyString_FromScalar ; 
 int RECORDOID ; 
 int /*<<< orphan*/  TYPECACHE_DOMAIN_BASE_INFO ; 
 char TYPTYPE_COMPOSITE ; 
 char TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  fmgr_info_cxt (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int,int*,int*) ; 
 int get_transform_fromsql (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* lookup_type_cache (int,int /*<<< orphan*/ ) ; 

void
PLy_input_setup_func(PLyDatumToOb *arg, MemoryContext arg_mcxt,
					 Oid typeOid, int32 typmod,
					 PLyProcedure *proc)
{
	TypeCacheEntry *typentry;
	char		typtype;
	Oid			trfuncid;
	Oid			typoutput;
	bool		typisvarlena;

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
		/* Domain --- we don't care, just recurse down to the base type */
		PLy_input_setup_func(arg, arg_mcxt,
							 typentry->domainBaseType,
							 typentry->domainBaseTypmod,
							 proc);
	}
	else if (typentry &&
			 OidIsValid(typentry->typelem) && typentry->typlen == -1)
	{
		/* Standard varlena array (cf. get_element_type) */
		arg->func = PLyList_FromArray;
		/* Recursively set up conversion info for the element type */
		arg->u.array.elm = (PLyDatumToOb *)
			MemoryContextAllocZero(arg_mcxt, sizeof(PLyDatumToOb));
		PLy_input_setup_func(arg->u.array.elm, arg_mcxt,
							 typentry->typelem, typmod,
							 proc);
	}
	else if ((trfuncid = get_transform_fromsql(typeOid,
											   proc->langid,
											   proc->trftypes)))
	{
		arg->func = PLyObject_FromTransform;
		fmgr_info_cxt(trfuncid, &arg->u.transform.typtransform, arg_mcxt);
	}
	else if (typtype == TYPTYPE_COMPOSITE)
	{
		/* Named composite type, or RECORD */
		arg->func = PLyDict_FromComposite;
		/* We'll set up the per-field data later */
		arg->u.tuple.recdesc = NULL;
		arg->u.tuple.typentry = typentry;
		arg->u.tuple.tupdescid = INVALID_TUPLEDESC_IDENTIFIER;
		arg->u.tuple.atts = NULL;
		arg->u.tuple.natts = 0;
	}
	else
	{
		/* Scalar type, but we have a couple of special cases */
		switch (typeOid)
		{
			case BOOLOID:
				arg->func = PLyBool_FromBool;
				break;
			case FLOAT4OID:
				arg->func = PLyFloat_FromFloat4;
				break;
			case FLOAT8OID:
				arg->func = PLyFloat_FromFloat8;
				break;
			case NUMERICOID:
				arg->func = PLyDecimal_FromNumeric;
				break;
			case INT2OID:
				arg->func = PLyInt_FromInt16;
				break;
			case INT4OID:
				arg->func = PLyInt_FromInt32;
				break;
			case INT8OID:
				arg->func = PLyLong_FromInt64;
				break;
			case OIDOID:
				arg->func = PLyLong_FromOid;
				break;
			case BYTEAOID:
				arg->func = PLyBytes_FromBytea;
				break;
			default:
				arg->func = PLyString_FromScalar;
				getTypeOutputInfo(typeOid, &typoutput, &typisvarlena);
				fmgr_info_cxt(typoutput, &arg->u.scalar.typfunc, arg_mcxt);
				break;
		}
	}
}