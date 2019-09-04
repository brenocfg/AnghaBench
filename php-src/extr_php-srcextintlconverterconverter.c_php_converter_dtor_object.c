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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  error; scalar_t__ dest; scalar_t__ src; } ;
typedef  TYPE_1__ php_converter_object ;

/* Variables and functions */
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ *) ; 
 TYPE_1__* php_converter_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucnv_close (scalar_t__) ; 

__attribute__((used)) static void php_converter_dtor_object(zend_object *obj) {
	php_converter_object *objval = php_converter_fetch_object(obj);

	if (objval->src) {
		ucnv_close(objval->src);
	}

	if (objval->dest) {
		ucnv_close(objval->dest);
	}

	intl_error_reset(&(objval->error));
}