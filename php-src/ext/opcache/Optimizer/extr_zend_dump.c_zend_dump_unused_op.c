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
struct TYPE_3__ {int num; } ;
typedef  TYPE_1__ znode_op ;
typedef  int /*<<< orphan*/  zend_op ;
typedef  int uint32_t ;

/* Variables and functions */
 int IS_CONSTANT_UNQUALIFIED_IN_NAMESPACE ; 
 int ZEND_VM_OP_CLASS_FETCH ; 
 int ZEND_VM_OP_CONSTRUCTOR ; 
 int ZEND_VM_OP_CONST_FETCH ; 
 int ZEND_VM_OP_MASK ; 
 int ZEND_VM_OP_NEXT ; 
 int ZEND_VM_OP_NUM ; 
 int ZEND_VM_OP_THIS ; 
 int ZEND_VM_OP_TRY_CATCH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_class_fetch_type (int) ; 

__attribute__((used)) static void zend_dump_unused_op(const zend_op *opline, znode_op op, uint32_t flags) {
	if (ZEND_VM_OP_NUM == (flags & ZEND_VM_OP_MASK)) {
		fprintf(stderr, " %u", op.num);
	} else if (ZEND_VM_OP_TRY_CATCH == (flags & ZEND_VM_OP_MASK)) {
		if (op.num != (uint32_t)-1) {
			fprintf(stderr, " try-catch(%u)", op.num);
		}
	} else if (ZEND_VM_OP_THIS == (flags & ZEND_VM_OP_MASK)) {
		fprintf(stderr, " THIS");
	} else if (ZEND_VM_OP_NEXT == (flags & ZEND_VM_OP_MASK)) {
		fprintf(stderr, " NEXT");
	} else if (ZEND_VM_OP_CLASS_FETCH == (flags & ZEND_VM_OP_MASK)) {
		zend_dump_class_fetch_type(op.num);
	} else if (ZEND_VM_OP_CONSTRUCTOR == (flags & ZEND_VM_OP_MASK)) {
		fprintf(stderr, " CONSTRUCTOR");
	} else if (ZEND_VM_OP_CONST_FETCH == (flags & ZEND_VM_OP_MASK)) {
		if (op.num & IS_CONSTANT_UNQUALIFIED_IN_NAMESPACE) {
			fprintf(stderr, " (unqualified-in-namespace)");
		}
	}
}