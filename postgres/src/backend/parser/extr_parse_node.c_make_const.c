#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  Value ;
struct TYPE_4__ {int location; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  ParseCallbackState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 int /*<<< orphan*/  BITOID ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int FLOAT8PASSBYVAL ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NUMERICOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
#define  T_BitString 132 
#define  T_Float 131 
#define  T_Integer 130 
#define  T_Null 129 
#define  T_String 128 
 int /*<<< orphan*/  UNKNOWNOID ; 
 int /*<<< orphan*/  bit_in ; 
 int /*<<< orphan*/  cancel_parser_errposition_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int intVal (int /*<<< orphan*/ *) ; 
 TYPE_1__* makeConst (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numeric_in ; 
 int /*<<< orphan*/  scanint8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_parser_errposition_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ *) ; 

Const *
make_const(ParseState *pstate, Value *value, int location)
{
	Const	   *con;
	Datum		val;
	int64		val64;
	Oid			typeid;
	int			typelen;
	bool		typebyval;
	ParseCallbackState pcbstate;

	switch (nodeTag(value))
	{
		case T_Integer:
			val = Int32GetDatum(intVal(value));

			typeid = INT4OID;
			typelen = sizeof(int32);
			typebyval = true;
			break;

		case T_Float:
			/* could be an oversize integer as well as a float ... */
			if (scanint8(strVal(value), true, &val64))
			{
				/*
				 * It might actually fit in int32. Probably only INT_MIN can
				 * occur, but we'll code the test generally just to be sure.
				 */
				int32		val32 = (int32) val64;

				if (val64 == (int64) val32)
				{
					val = Int32GetDatum(val32);

					typeid = INT4OID;
					typelen = sizeof(int32);
					typebyval = true;
				}
				else
				{
					val = Int64GetDatum(val64);

					typeid = INT8OID;
					typelen = sizeof(int64);
					typebyval = FLOAT8PASSBYVAL;	/* int8 and float8 alike */
				}
			}
			else
			{
				/* arrange to report location if numeric_in() fails */
				setup_parser_errposition_callback(&pcbstate, pstate, location);
				val = DirectFunctionCall3(numeric_in,
										  CStringGetDatum(strVal(value)),
										  ObjectIdGetDatum(InvalidOid),
										  Int32GetDatum(-1));
				cancel_parser_errposition_callback(&pcbstate);

				typeid = NUMERICOID;
				typelen = -1;	/* variable len */
				typebyval = false;
			}
			break;

		case T_String:

			/*
			 * We assume here that UNKNOWN's internal representation is the
			 * same as CSTRING
			 */
			val = CStringGetDatum(strVal(value));

			typeid = UNKNOWNOID;	/* will be coerced later */
			typelen = -2;		/* cstring-style varwidth type */
			typebyval = false;
			break;

		case T_BitString:
			/* arrange to report location if bit_in() fails */
			setup_parser_errposition_callback(&pcbstate, pstate, location);
			val = DirectFunctionCall3(bit_in,
									  CStringGetDatum(strVal(value)),
									  ObjectIdGetDatum(InvalidOid),
									  Int32GetDatum(-1));
			cancel_parser_errposition_callback(&pcbstate);
			typeid = BITOID;
			typelen = -1;
			typebyval = false;
			break;

		case T_Null:
			/* return a null const */
			con = makeConst(UNKNOWNOID,
							-1,
							InvalidOid,
							-2,
							(Datum) 0,
							true,
							false);
			con->location = location;
			return con;

		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(value));
			return NULL;		/* keep compiler quiet */
	}

	con = makeConst(typeid,
					-1,			/* typmod -1 is OK for all cases */
					InvalidOid, /* all cases are uncollatable types */
					typelen,
					val,
					false,
					typebyval);
	con->location = location;

	return con;
}