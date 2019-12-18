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
#define  ECPGt_bool 150 
#define  ECPGt_bytea 149 
#define  ECPGt_char 148 
#define  ECPGt_char_variable 147 
#define  ECPGt_const 146 
#define  ECPGt_date 145 
#define  ECPGt_decimal 144 
#define  ECPGt_double 143 
#define  ECPGt_float 142 
#define  ECPGt_int 141 
#define  ECPGt_interval 140 
#define  ECPGt_long 139 
#define  ECPGt_long_long 138 
#define  ECPGt_numeric 137 
#define  ECPGt_short 136 
#define  ECPGt_string 135 
#define  ECPGt_timestamp 134 
#define  ECPGt_unsigned_char 133 
#define  ECPGt_unsigned_int 132 
#define  ECPGt_unsigned_long 131 
#define  ECPGt_unsigned_long_long 130 
#define  ECPGt_unsigned_short 129 
#define  ECPGt_varchar 128 
 int /*<<< orphan*/  abort () ; 

const char *
ecpg_type_name(enum ECPGttype typ)
{
	switch (typ)
	{
		case ECPGt_char:
		case ECPGt_string:
			return "char";
		case ECPGt_unsigned_char:
			return "unsigned char";
		case ECPGt_short:
			return "short";
		case ECPGt_unsigned_short:
			return "unsigned short";
		case ECPGt_int:
			return "int";
		case ECPGt_unsigned_int:
			return "unsigned int";
		case ECPGt_long:
			return "long";
		case ECPGt_unsigned_long:
			return "unsigned long";
		case ECPGt_long_long:
			return "long long";
		case ECPGt_unsigned_long_long:
			return "unsigned long long";
		case ECPGt_float:
			return "float";
		case ECPGt_double:
			return "double";
		case ECPGt_bool:
			return "bool";
		case ECPGt_varchar:
			return "varchar";
		case ECPGt_bytea:
			return "bytea";
		case ECPGt_char_variable:
			return "char";
		case ECPGt_decimal:
			return "decimal";
		case ECPGt_numeric:
			return "numeric";
		case ECPGt_date:
			return "date";
		case ECPGt_timestamp:
			return "timestamp";
		case ECPGt_interval:
			return "interval";
		case ECPGt_const:
			return "Const";
		default:
			abort();
	}
	return "";					/* keep MSC compiler happy */
}