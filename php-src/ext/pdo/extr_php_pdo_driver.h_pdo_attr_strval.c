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
typedef  int /*<<< orphan*/  zend_string ;
typedef  enum pdo_attribute_type { ____Placeholder_pdo_attribute_type } pdo_attribute_type ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_try_get_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline zend_string *pdo_attr_strval(zval *options, enum pdo_attribute_type option_name, zend_string *defval)
{
	zval *v;

	if (options && (v = zend_hash_index_find(Z_ARRVAL_P(options), option_name))) {
		return zval_try_get_string(v);
	}
	return defval ? zend_string_copy(defval) : NULL;
}