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

__attribute__((used)) static const char *
descriptor_item_name(enum ECPGdtype itemcode)
{
	switch (itemcode)
	{
		case ECPGd_cardinality:
			return "CARDINALITY";
		case ECPGd_count:
			return "COUNT";
		case ECPGd_data:
			return "DATA";
		case ECPGd_di_code:
			return "DATETIME_INTERVAL_CODE";
		case ECPGd_di_precision:
			return "DATETIME_INTERVAL_PRECISION";
		case ECPGd_indicator:
			return "INDICATOR";
		case ECPGd_key_member:
			return "KEY_MEMBER";
		case ECPGd_length:
			return "LENGTH";
		case ECPGd_name:
			return "NAME";
		case ECPGd_nullable:
			return "NULLABLE";
		case ECPGd_octet:
			return "OCTET_LENGTH";
		case ECPGd_precision:
			return "PRECISION";
		case ECPGd_ret_length:
			return "RETURNED_LENGTH";
		case ECPGd_ret_octet:
			return "RETURNED_OCTET_LENGTH";
		case ECPGd_scale:
			return "SCALE";
		case ECPGd_type:
			return "TYPE";
		default:
			return NULL;
	}
}