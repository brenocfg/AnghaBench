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
typedef  int uint32_t ;

/* Variables and functions */
 int IS_ARRAY ; 
 int IS_OBJECT ; 
 int PARTIAL_ARRAY ; 
 int PARTIAL_OBJECT ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ct_eval_type_check(zval *result, uint32_t type_mask, zval *op1) {
	uint32_t type = Z_TYPE_P(op1);
	if (type == PARTIAL_ARRAY) {
		type = IS_ARRAY;
	} else if (type == PARTIAL_OBJECT) {
		type = IS_OBJECT;
	}
	ZVAL_BOOL(result, (type_mask >> type) & 1);
}