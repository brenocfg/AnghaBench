#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ zend_op_array ;
typedef  int /*<<< orphan*/  phpdbg_breakbase_t ;
struct TYPE_7__ {TYPE_1__* opline; } ;
struct TYPE_5__ {int /*<<< orphan*/  lineno; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 TYPE_4__* EG (int /*<<< orphan*/ ) ; 
 size_t PHPDBG_BREAK_FILE ; 
 int /*<<< orphan*/ * PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/  current_execute_data ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline phpdbg_breakbase_t *phpdbg_find_breakpoint_file(zend_op_array *op_array) /* {{{ */
{
	HashTable *breaks;
	phpdbg_breakbase_t *brake;

#if 0
	phpdbg_debug("Op at: %.*s %d\n", ZSTR_LEN(op_array->filename), ZSTR_VAL(op_array->filename), (*EG(opline_ptr))->lineno);
#endif

	/* NOTE: realpath resolution should have happened at compile time - no reason to do it here again */
	if (!(breaks = zend_hash_find_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_FILE], op_array->filename))) {
		return NULL;
	}

	if (EG(current_execute_data) && (brake = zend_hash_index_find_ptr(breaks, EG(current_execute_data)->opline->lineno))) {
		return brake;
	}

	return NULL;
}