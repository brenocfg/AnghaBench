#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  BOOLOID 145 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetFloat4 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt16 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  FLOAT4OID 144 
#define  FLOAT8OID 143 
#define  INT2OID 142 
#define  INT4OID 141 
#define  INT8OID 140 
#define  NUMERICOID 139 
#define  OIDOID 138 
#define  REGCLASSOID 137 
#define  REGCONFIGOID 136 
#define  REGDICTIONARYOID 135 
#define  REGNAMESPACEOID 134 
#define  REGOPERATOROID 133 
#define  REGOPEROID 132 
#define  REGPROCEDUREOID 131 
#define  REGPROCOID 130 
#define  REGROLEOID 129 
#define  REGTYPEOID 128 
 int /*<<< orphan*/  numeric_float8_no_overflow ; 

__attribute__((used)) static double
convert_numeric_to_scalar(Datum value, Oid typid, bool *failure)
{
	switch (typid)
	{
		case BOOLOID:
			return (double) DatumGetBool(value);
		case INT2OID:
			return (double) DatumGetInt16(value);
		case INT4OID:
			return (double) DatumGetInt32(value);
		case INT8OID:
			return (double) DatumGetInt64(value);
		case FLOAT4OID:
			return (double) DatumGetFloat4(value);
		case FLOAT8OID:
			return (double) DatumGetFloat8(value);
		case NUMERICOID:
			/* Note: out-of-range values will be clamped to +-HUGE_VAL */
			return (double)
				DatumGetFloat8(DirectFunctionCall1(numeric_float8_no_overflow,
												   value));
		case OIDOID:
		case REGPROCOID:
		case REGPROCEDUREOID:
		case REGOPEROID:
		case REGOPERATOROID:
		case REGCLASSOID:
		case REGTYPEOID:
		case REGCONFIGOID:
		case REGDICTIONARYOID:
		case REGROLEOID:
		case REGNAMESPACEOID:
			/* we can treat OIDs as integers... */
			return (double) DatumGetObjectId(value);
	}

	*failure = true;
	return 0;
}