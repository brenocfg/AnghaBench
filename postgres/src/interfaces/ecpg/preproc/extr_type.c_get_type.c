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
#define  ECPGt_NO_INDICATOR 153 
#define  ECPGt_bool 152 
#define  ECPGt_bytea 151 
#define  ECPGt_char 150 
#define  ECPGt_char_variable 149 
#define  ECPGt_const 148 
#define  ECPGt_date 147 
#define  ECPGt_decimal 146 
#define  ECPGt_descriptor 145 
#define  ECPGt_double 144 
#define  ECPGt_float 143 
#define  ECPGt_int 142 
#define  ECPGt_interval 141 
#define  ECPGt_long 140 
#define  ECPGt_long_long 139 
#define  ECPGt_numeric 138 
#define  ECPGt_short 137 
#define  ECPGt_sqlda 136 
#define  ECPGt_string 135 
#define  ECPGt_timestamp 134 
#define  ECPGt_unsigned_char 133 
#define  ECPGt_unsigned_int 132 
#define  ECPGt_unsigned_long 131 
#define  ECPGt_unsigned_long_long 130 
#define  ECPGt_unsigned_short 129 
#define  ECPGt_varchar 128 
 int /*<<< orphan*/  ET_ERROR ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static const char *
get_type(enum ECPGttype type)
{
	switch (type)
	{
		case ECPGt_char:
			return "ECPGt_char";
			break;
		case ECPGt_unsigned_char:
			return "ECPGt_unsigned_char";
			break;
		case ECPGt_short:
			return "ECPGt_short";
			break;
		case ECPGt_unsigned_short:
			return "ECPGt_unsigned_short";
			break;
		case ECPGt_int:
			return "ECPGt_int";
			break;
		case ECPGt_unsigned_int:
			return "ECPGt_unsigned_int";
			break;
		case ECPGt_long:
			return "ECPGt_long";
			break;
		case ECPGt_unsigned_long:
			return "ECPGt_unsigned_long";
			break;
		case ECPGt_long_long:
			return "ECPGt_long_long";
			break;
		case ECPGt_unsigned_long_long:
			return "ECPGt_unsigned_long_long";
			break;
		case ECPGt_float:
			return "ECPGt_float";
			break;
		case ECPGt_double:
			return "ECPGt_double";
			break;
		case ECPGt_bool:
			return "ECPGt_bool";
			break;
		case ECPGt_varchar:
			return "ECPGt_varchar";
		case ECPGt_bytea:
			return "ECPGt_bytea";
		case ECPGt_NO_INDICATOR:	/* no indicator */
			return "ECPGt_NO_INDICATOR";
			break;
		case ECPGt_char_variable:	/* string that should not be quoted */
			return "ECPGt_char_variable";
			break;
		case ECPGt_const:		/* constant string quoted */
			return "ECPGt_const";
			break;
		case ECPGt_decimal:
			return "ECPGt_decimal";
			break;
		case ECPGt_numeric:
			return "ECPGt_numeric";
			break;
		case ECPGt_interval:
			return "ECPGt_interval";
			break;
		case ECPGt_descriptor:
			return "ECPGt_descriptor";
			break;
		case ECPGt_sqlda:
			return "ECPGt_sqlda";
			break;
		case ECPGt_date:
			return "ECPGt_date";
			break;
		case ECPGt_timestamp:
			return "ECPGt_timestamp";
			break;
		case ECPGt_string:
			return "ECPGt_string";
			break;
		default:
			mmerror(PARSE_ERROR, ET_ERROR, "unrecognized variable type code %d", type);
	}

	return NULL;
}