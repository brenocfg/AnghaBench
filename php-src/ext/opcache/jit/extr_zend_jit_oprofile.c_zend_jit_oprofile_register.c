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
typedef  scalar_t__ zend_uintptr_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ op_agent ; 
 int /*<<< orphan*/  op_write_native_code (scalar_t__,char const*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static void zend_jit_oprofile_register(const char *name,
                                       const void *start,
                                       size_t      size)
{
	if (op_agent) {
		op_write_native_code(op_agent, name, (uint64_t)(zend_uintptr_t)start, start, size);
	}
}