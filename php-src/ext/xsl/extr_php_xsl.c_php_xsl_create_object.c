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
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  scalar_t__ xsltStylesheetPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_xsl_set_object (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * xsl_object_get_data (void*) ; 
 int /*<<< orphan*/ * xsl_xsltprocessor_class_entry ; 

void php_xsl_create_object(xsltStylesheetPtr obj, zval *wrapper_in, zval *return_value )
{
	zval *wrapper;
	zend_class_entry *ce;

	if (!obj) {
		wrapper = wrapper_in;
		ZVAL_NULL(wrapper);
		return;
	}

	if ((wrapper = xsl_object_get_data((void *) obj))) {
		ZVAL_COPY(wrapper, wrapper_in);
		return;
	}

	if (!wrapper_in) {
		wrapper = return_value;
	} else {
		wrapper = wrapper_in;
	}


	ce = xsl_xsltprocessor_class_entry;

	if (!wrapper_in) {
		object_init_ex(wrapper, ce);
	}
	php_xsl_set_object(wrapper, (void *) obj);

	return;
}