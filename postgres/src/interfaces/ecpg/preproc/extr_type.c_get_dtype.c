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
typedef  enum ECPGdtype { ____Placeholder_ECPGdtype } ECPGdtype ;

/* Variables and functions */
#define  ECPGd_cardinality 143 
#define  ECPGd_count 142 
#define  ECPGd_data 141 
#define  ECPGd_di_code 140 
#define  ECPGd_di_precision 139 
#define  ECPGd_indicator 138 
#define  ECPGd_key_member 137 
#define  ECPGd_length 136 
#define  ECPGd_name 135 
#define  ECPGd_nullable 134 
#define  ECPGd_octet 133 
#define  ECPGd_precision 132 
#define  ECPGd_ret_length 131 
#define  ECPGd_ret_octet 130 
#define  ECPGd_scale 129 
#define  ECPGd_type 128 
 int /*<<< orphan*/  ET_ERROR ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

const char *
get_dtype(enum ECPGdtype type)
{
	switch (type)
	{
		case ECPGd_count:
			return "ECPGd_countr";
			break;
		case ECPGd_data:
			return "ECPGd_data";
			break;
		case ECPGd_di_code:
			return "ECPGd_di_code";
			break;
		case ECPGd_di_precision:
			return "ECPGd_di_precision";
			break;
		case ECPGd_indicator:
			return "ECPGd_indicator";
			break;
		case ECPGd_key_member:
			return "ECPGd_key_member";
			break;
		case ECPGd_length:
			return "ECPGd_length";
			break;
		case ECPGd_name:
			return "ECPGd_name";
			break;
		case ECPGd_nullable:
			return "ECPGd_nullable";
			break;
		case ECPGd_octet:
			return "ECPGd_octet";
			break;
		case ECPGd_precision:
			return "ECPGd_precision";
			break;
		case ECPGd_ret_length:
			return "ECPGd_ret_length";
		case ECPGd_ret_octet:
			return "ECPGd_ret_octet";
			break;
		case ECPGd_scale:
			return "ECPGd_scale";
			break;
		case ECPGd_type:
			return "ECPGd_type";
			break;
		case ECPGd_cardinality:
			return "ECPGd_cardinality";
		default:
			mmerror(PARSE_ERROR, ET_ERROR, "unrecognized descriptor item code %d", type);
	}

	return NULL;
}