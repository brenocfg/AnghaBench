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
struct TYPE_3__ {scalar_t__ opcode; } ;
typedef  TYPE_1__ zend_op ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ ZEND_ADD_ARRAY_ELEMENT ; 
 scalar_t__ ZEND_ROPE_ADD ; 

__attribute__((used)) static zend_bool is_fake_def(zend_op *opline) {
	/* These opcodes only modify the result, not create it. */
	return opline->opcode == ZEND_ROPE_ADD
		|| opline->opcode == ZEND_ADD_ARRAY_ELEMENT;
}