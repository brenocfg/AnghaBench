#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/ * doc_comment; int /*<<< orphan*/ * name; struct TYPE_8__* ce; } ;
typedef  TYPE_1__ zend_property_info ;
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UNSERIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZEND_TYPE_ALLOW_NULL (scalar_t__) ; 
 TYPE_1__* ZEND_TYPE_CE (scalar_t__) ; 
 scalar_t__ ZEND_TYPE_ENCODE_CE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_ENCODE_CLASS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_CE (scalar_t__) ; 
 scalar_t__ ZEND_TYPE_IS_NAME (scalar_t__) ; 
 int /*<<< orphan*/ * ZEND_TYPE_NAME (scalar_t__) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_file_cache_unserialize_prop_info(zval                    *zv,
                                                  zend_persistent_script  *script,
                                                  void                    *buf)
{
	if (!IS_UNSERIALIZED(Z_PTR_P(zv))) {
		zend_property_info *prop;

		UNSERIALIZE_PTR(Z_PTR_P(zv));
		prop = Z_PTR_P(zv);

		ZEND_ASSERT(prop->ce != NULL && prop->name != NULL);
		if (!IS_UNSERIALIZED(prop->ce)) {
			UNSERIALIZE_PTR(prop->ce);
			UNSERIALIZE_STR(prop->name);
			if (prop->doc_comment) {
				UNSERIALIZE_STR(prop->doc_comment);
			}
		}
		if (prop->type) {
			if (ZEND_TYPE_IS_NAME(prop->type)) {
				zend_string *name = ZEND_TYPE_NAME(prop->type);
				UNSERIALIZE_STR(name);
				prop->type = ZEND_TYPE_ENCODE_CLASS(name, ZEND_TYPE_ALLOW_NULL(prop->type));
			} else if (ZEND_TYPE_IS_CE(prop->type)) {
				zend_class_entry *ce = ZEND_TYPE_CE(prop->type);
				UNSERIALIZE_PTR(ce);
				prop->type = ZEND_TYPE_ENCODE_CE(ce, ZEND_TYPE_ALLOW_NULL(prop->type));
			}
		}
	}
}