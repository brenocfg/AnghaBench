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
typedef  int /*<<< orphan*/  mysqli_object ;

/* Variables and functions */
 scalar_t__ MyG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  error_msg ; 

__attribute__((used)) static zval *link_connect_error_read(mysqli_object *obj, zval *retval)
{
	if (MyG(error_msg)) {
		ZVAL_STRING(retval, MyG(error_msg));
	} else {
		ZVAL_NULL(retval);
	}
	return retval;
}