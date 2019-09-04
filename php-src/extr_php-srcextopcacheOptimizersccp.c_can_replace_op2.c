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
typedef  int /*<<< orphan*/  zend_ssa_op ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_3__ {int opcode; } ;
typedef  TYPE_1__ zend_op ;
typedef  int zend_bool ;

/* Variables and functions */
#define  ZEND_BIND_LEXICAL 133 
#define  ZEND_DECLARE_ANON_INHERITED_CLASS 132 
#define  ZEND_DECLARE_INHERITED_CLASS 131 
#define  ZEND_DECLARE_INHERITED_CLASS_DELAYED 130 
#define  ZEND_FE_FETCH_R 129 
#define  ZEND_FE_FETCH_RW 128 

__attribute__((used)) static zend_bool can_replace_op2(
		const zend_op_array *op_array, zend_op *opline, zend_ssa_op *ssa_op) {
	switch (opline->opcode) {
		/* Do not accept CONST */
		case ZEND_DECLARE_INHERITED_CLASS:
		case ZEND_DECLARE_INHERITED_CLASS_DELAYED:
		case ZEND_DECLARE_ANON_INHERITED_CLASS:
		case ZEND_BIND_LEXICAL:
		case ZEND_FE_FETCH_R:
		case ZEND_FE_FETCH_RW:
			return 0;
	}
	return 1;
}