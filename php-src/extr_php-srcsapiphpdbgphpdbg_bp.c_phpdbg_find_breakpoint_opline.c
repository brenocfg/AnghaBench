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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  scalar_t__ phpdbg_opline_ptr_t ;
struct TYPE_3__ {scalar_t__ base; } ;
typedef  TYPE_1__ phpdbg_breakline_t ;
typedef  int /*<<< orphan*/  phpdbg_breakbase_t ;

/* Variables and functions */
 size_t PHPDBG_BREAK_OPLINE ; 
 int /*<<< orphan*/ * PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp ; 
 TYPE_1__* zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline phpdbg_breakbase_t *phpdbg_find_breakpoint_opline(phpdbg_opline_ptr_t opline) /* {{{ */
{
	phpdbg_breakline_t *brake;

	if ((brake = zend_hash_index_find_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_OPLINE], (zend_ulong) opline)) && brake->base) {
		return (phpdbg_breakbase_t *)brake->base;
	}

	return (phpdbg_breakbase_t *) brake;
}