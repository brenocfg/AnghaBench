#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode ;
struct TYPE_5__ {int /*<<< orphan*/  extended_value; } ;
typedef  TYPE_1__ zend_op ;
typedef  int /*<<< orphan*/  zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_FETCH_REF ; 
 int /*<<< orphan*/  zend_delayed_compile_begin () ; 
 TYPE_1__* zend_delayed_compile_end (int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_delayed_compile_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_op *zend_compile_prop(znode *result, zend_ast *ast, uint32_t type, int by_ref) /* {{{ */
{
	uint32_t offset = zend_delayed_compile_begin();
	zend_op *opline = zend_delayed_compile_prop(result, ast, type);
	if (by_ref) { /* shared with cache_slot */
		opline->extended_value |= ZEND_FETCH_REF;
	}
	return zend_delayed_compile_end(offset);
}