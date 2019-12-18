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
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  phpdbg_breakbase_t ;

/* Variables and functions */
 size_t PHPDBG_BREAK_OPCODE ; 
 int /*<<< orphan*/ * PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* zend_get_opcode_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_func (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline phpdbg_breakbase_t *phpdbg_find_breakpoint_opcode(zend_uchar opcode) /* {{{ */
{
	const char *opname = zend_get_opcode_name(opcode);

	if (!opname) {
		return NULL;
	}

	return zend_hash_index_find_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_OPCODE], zend_hash_func(opname, strlen(opname)));
}