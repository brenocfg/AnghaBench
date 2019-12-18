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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;

/* Variables and functions */
 int /*<<< orphan*/  INCOMPLETE_CLASS_MSG ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * php_lookup_class_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void incomplete_class_message(zend_object *object, int error_type)
{
	zend_string *class_name;

	class_name = php_lookup_class_name(object);

	if (class_name) {
		php_error_docref(NULL, error_type, INCOMPLETE_CLASS_MSG, ZSTR_VAL(class_name));
		zend_string_release_ex(class_name, 0);
	} else {
		php_error_docref(NULL, error_type, INCOMPLETE_CLASS_MSG, "unknown");
	}
}