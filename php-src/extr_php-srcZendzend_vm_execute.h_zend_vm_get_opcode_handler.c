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
typedef  size_t zend_uchar ;
typedef  int /*<<< orphan*/  zend_op ;

/* Variables and functions */
 int /*<<< orphan*/ * zend_spec_handlers ; 
 void const* zend_vm_get_opcode_handler_ex (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const void *zend_vm_get_opcode_handler(zend_uchar opcode, const zend_op* op)
{
	return zend_vm_get_opcode_handler_ex(zend_spec_handlers[opcode], op);
}