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
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_table ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_lookup_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_class_entry * spl_find_ce_by_name(zend_string *name, zend_bool autoload)
{
	zend_class_entry *ce;

	if (!autoload) {
		zend_string *lc_name = zend_string_tolower(name);

		ce = zend_hash_find_ptr(EG(class_table), lc_name);
		zend_string_release(lc_name);
	} else {
 		ce = zend_lookup_class(name);
 	}
 	if (ce == NULL) {
		php_error_docref(NULL, E_WARNING, "Class %s does not exist%s", ZSTR_VAL(name), autoload ? " and could not be loaded" : "");
		return NULL;
	}

	return ce;
}