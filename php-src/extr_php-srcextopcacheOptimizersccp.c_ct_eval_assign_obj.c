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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_FALSE 130 
#define  IS_NULL 129 
#define  PARTIAL_OBJECT 128 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int ct_eval_add_obj_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty_partial_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_assign_obj(zval *result, zval *value, zval *key) {
	switch (Z_TYPE_P(result)) {
		case IS_NULL:
		case IS_FALSE:
			empty_partial_object(result);
			/* break missing intentionally */
		case PARTIAL_OBJECT:
			return ct_eval_add_obj_prop(result, value, key);
		default:
			return FAILURE;
	}
}