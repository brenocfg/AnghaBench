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
typedef  enum COMPAT_MODE { ____Placeholder_COMPAT_MODE } COMPAT_MODE ;
typedef  int Oid ;

/* Variables and functions */
#define  BPCHAROID 141 
#define  CHAROID 140 
#define  DATEOID 139 
 int ECPGt_char ; 
 int ECPGt_date ; 
 int ECPGt_decimal ; 
 int ECPGt_double ; 
 int ECPGt_float ; 
 int ECPGt_int ; 
 int ECPGt_interval ; 
 int ECPGt_long ; 
 int ECPGt_long_long ; 
 int ECPGt_numeric ; 
 int ECPGt_short ; 
 int ECPGt_timestamp ; 
#define  FLOAT4OID 138 
#define  FLOAT8OID 137 
 int /*<<< orphan*/  INFORMIX_MODE (int) ; 
#define  INT2OID 136 
#define  INT4OID 135 
#define  INT8OID 134 
#define  INTERVALOID 133 
#define  NUMERICOID 132 
#define  TEXTOID 131 
#define  TIMESTAMPOID 130 
#define  TIMESTAMPTZOID 129 
#define  VARCHAROID 128 

int
sqlda_dynamic_type(Oid type, enum COMPAT_MODE compat)
{
	switch (type)
	{
		case CHAROID:
		case VARCHAROID:
		case BPCHAROID:
		case TEXTOID:
			return ECPGt_char;
		case INT2OID:
			return ECPGt_short;
		case INT4OID:
			return ECPGt_int;
		case FLOAT8OID:
			return ECPGt_double;
		case FLOAT4OID:
			return ECPGt_float;
		case NUMERICOID:
			return INFORMIX_MODE(compat) ? ECPGt_decimal : ECPGt_numeric;
		case DATEOID:
			return ECPGt_date;
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
			return ECPGt_timestamp;
		case INTERVALOID:
			return ECPGt_interval;
		case INT8OID:
#ifdef HAVE_LONG_LONG_INT_64
			return ECPGt_long_long;
#endif
#ifdef HAVE_LONG_INT_64
			return ECPGt_long;
#endif
			/* Unhandled types always return a string */
		default:
			return ECPGt_char;
	}
}