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
typedef  enum ECPGttype { ____Placeholder_ECPGttype } ECPGttype ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION ; 
 int /*<<< orphan*/  ECPG_VAR_NOT_NUMERIC ; 
#define  ECPGt_double 137 
#define  ECPGt_float 136 
#define  ECPGt_int 135 
#define  ECPGt_long 134 
#define  ECPGt_long_long 133 
#define  ECPGt_short 132 
#define  ECPGt_unsigned_int 131 
#define  ECPGt_unsigned_long 130 
#define  ECPGt_unsigned_long_long 129 
#define  ECPGt_unsigned_short 128 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
get_int_item(int lineno, void *var, enum ECPGttype vartype, int value)
{
	switch (vartype)
	{
		case ECPGt_short:
			*(short *) var = (short) value;
			break;
		case ECPGt_int:
			*(int *) var = (int) value;
			break;
		case ECPGt_long:
			*(long *) var = (long) value;
			break;
		case ECPGt_unsigned_short:
			*(unsigned short *) var = (unsigned short) value;
			break;
		case ECPGt_unsigned_int:
			*(unsigned int *) var = (unsigned int) value;
			break;
		case ECPGt_unsigned_long:
			*(unsigned long *) var = (unsigned long) value;
			break;
		case ECPGt_long_long:
			*(long long int *) var = (long long int) value;
			break;
		case ECPGt_unsigned_long_long:
			*(unsigned long long int *) var = (unsigned long long int) value;
			break;
		case ECPGt_float:
			*(float *) var = (float) value;
			break;
		case ECPGt_double:
			*(double *) var = (double) value;
			break;
		default:
			ecpg_raise(lineno, ECPG_VAR_NOT_NUMERIC, ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION, NULL);
			return false;
	}

	return true;
}