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
#define  CASHOID 137 
#define  CIDOID 136 
#define  FLOAT4OID 135 
#define  FLOAT8OID 134 
#define  INT2OID 133 
#define  INT4OID 132 
#define  INT8OID 131 
#define  NUMERICOID 130 
#define  OIDOID 129 
#define  XIDOID 128 

char
column_type_alignment(Oid ftype)
{
	char		align;

	switch (ftype)
	{
		case INT2OID:
		case INT4OID:
		case INT8OID:
		case FLOAT4OID:
		case FLOAT8OID:
		case NUMERICOID:
		case OIDOID:
		case XIDOID:
		case CIDOID:
		case CASHOID:
			align = 'r';
			break;
		default:
			align = 'l';
			break;
	}
	return align;
}