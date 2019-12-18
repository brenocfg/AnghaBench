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
set_int_item(int lineno, int *target, const void *var, enum ECPGttype vartype)
{
	switch (vartype)
	{
		case ECPGt_short:
			*target = *(const short *) var;
			break;
		case ECPGt_int:
			*target = *(const int *) var;
			break;
		case ECPGt_long:
			*target = *(const long *) var;
			break;
		case ECPGt_unsigned_short:
			*target = *(const unsigned short *) var;
			break;
		case ECPGt_unsigned_int:
			*target = *(const unsigned int *) var;
			break;
		case ECPGt_unsigned_long:
			*target = *(const unsigned long *) var;
			break;
		case ECPGt_long_long:
			*target = *(const long long int *) var;
			break;
		case ECPGt_unsigned_long_long:
			*target = *(const unsigned long long int *) var;
			break;
		case ECPGt_float:
			*target = *(const float *) var;
			break;
		case ECPGt_double:
			*target = *(const double *) var;
			break;
		default:
			ecpg_raise(lineno, ECPG_VAR_NOT_NUMERIC, ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION, NULL);
			return false;
	}

	return true;
}