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
 int /*<<< orphan*/  RETURN_FALSE ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _default_load_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _default_get_name(zval *object, zval *return_value) /* {{{ */
{
	zval *value;

	if ((value = _default_load_name(object)) == NULL) {
		RETURN_FALSE;
	}
	ZVAL_COPY(return_value, value);
}