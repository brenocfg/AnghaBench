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

/* Variables and functions */
#define  BOOLOID 139 
#define  BPCHAROID 138 
#define  DATEOID 137 
#define  FLOAT4OID 136 
#define  FLOAT8OID 135 
#define  INT2OID 134 
#define  INT4OID 133 
#define  NUMERICOID 132 
 int SQL3_BOOLEAN ; 
 int SQL3_CHARACTER ; 
 int SQL3_CHARACTER_VARYING ; 
 int SQL3_DATE_TIME_TIMESTAMP ; 
 int SQL3_DOUBLE_PRECISION ; 
 int SQL3_INTEGER ; 
 int SQL3_NUMERIC ; 
 int SQL3_REAL ; 
 int SQL3_SMALLINT ; 
#define  TEXTOID 131 
#define  TIMEOID 130 
#define  TIMESTAMPOID 129 
#define  VARCHAROID 128 

int
ecpg_dynamic_type(Oid type)
{
	switch (type)
	{
		case BOOLOID:
			return SQL3_BOOLEAN;	/* bool */
		case INT2OID:
			return SQL3_SMALLINT;	/* int2 */
		case INT4OID:
			return SQL3_INTEGER;	/* int4 */
		case TEXTOID:
			return SQL3_CHARACTER;	/* text */
		case FLOAT4OID:
			return SQL3_REAL;	/* float4 */
		case FLOAT8OID:
			return SQL3_DOUBLE_PRECISION;	/* float8 */
		case BPCHAROID:
			return SQL3_CHARACTER;	/* bpchar */
		case VARCHAROID:
			return SQL3_CHARACTER_VARYING;	/* varchar */
		case DATEOID:
			return SQL3_DATE_TIME_TIMESTAMP;	/* date */
		case TIMEOID:
			return SQL3_DATE_TIME_TIMESTAMP;	/* time */
		case TIMESTAMPOID:
			return SQL3_DATE_TIME_TIMESTAMP;	/* datetime */
		case NUMERICOID:
			return SQL3_NUMERIC;	/* numeric */
		default:
			return 0;
	}
}