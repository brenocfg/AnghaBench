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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_COMPARE_OBJECTS_FALLBACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zend_closure_compare(zval *o1, zval *o2) /* {{{ */
{
	ZEND_COMPARE_OBJECTS_FALLBACK(o1, o2);
	return Z_OBJ_P(o1) != Z_OBJ_P(o2);
}