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
typedef  int /*<<< orphan*/  znode ;
typedef  int /*<<< orphan*/  zend_op ;
typedef  int /*<<< orphan*/  zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  zend_delayed_compile_begin () ; 
 int /*<<< orphan*/  zend_delayed_compile_dim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_delayed_compile_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_op *zend_compile_dim(znode *result, zend_ast *ast, uint32_t type) /* {{{ */
{
	uint32_t offset = zend_delayed_compile_begin();
	zend_delayed_compile_dim(result, ast, type);
	return zend_delayed_compile_end(offset);
}