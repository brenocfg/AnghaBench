#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  int /*<<< orphan*/  RCFValueString ;
typedef  int /*<<< orphan*/  RCFValueNULL ;
typedef  int /*<<< orphan*/  RCFValueInteger ;
typedef  int /*<<< orphan*/  RCFValueDict ;
typedef  int /*<<< orphan*/  RCFValueData ;
typedef  int /*<<< orphan*/  RCFValueBool ;
typedef  int /*<<< orphan*/  RCFValueArray ;
typedef  TYPE_1__ RCFValue ;

/* Variables and functions */
#define  R_CF_ARRAY 135 
#define  R_CF_DATA 134 
#define  R_CF_DICT 133 
#define  R_CF_FALSE 132 
#define  R_CF_INTEGER 131 
#define  R_CF_NULL 130 
#define  R_CF_STRING 129 
#define  R_CF_TRUE 128 
 int /*<<< orphan*/  r_cf_value_array_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cf_value_bool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cf_value_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cf_value_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cf_value_integer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cf_value_null_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cf_value_string_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_cf_value_free(RCFValue *value) {
	if (!value) {
		return;
	}

	switch (value->type) {
	case R_CF_DICT:
		r_cf_value_dict_free ((RCFValueDict *)value);
		break;
	case R_CF_ARRAY:
		r_cf_value_array_free ((RCFValueArray *)value);
		break;
	case R_CF_STRING:
		r_cf_value_string_free ((RCFValueString *)value);
		break;
	case R_CF_INTEGER:
		r_cf_value_integer_free ((RCFValueInteger *)value);
		break;
	case R_CF_DATA:
		r_cf_value_data_free ((RCFValueData *)value);
		break;
	case R_CF_NULL:
		r_cf_value_null_free ((RCFValueNULL *)value);
		break;
	case R_CF_TRUE:
	case R_CF_FALSE:
		r_cf_value_bool_free ((RCFValueBool *)value);
		break;
	default:
		break;
	}
}