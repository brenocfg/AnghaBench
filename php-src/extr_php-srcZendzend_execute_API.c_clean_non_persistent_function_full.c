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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ zend_function ;

/* Variables and functions */
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_REMOVE ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clean_non_persistent_function_full(zval *zv) /* {{{ */
{
	zend_function *function = Z_PTR_P(zv);
	return (function->type == ZEND_INTERNAL_FUNCTION) ? ZEND_HASH_APPLY_KEEP : ZEND_HASH_APPLY_REMOVE;
}