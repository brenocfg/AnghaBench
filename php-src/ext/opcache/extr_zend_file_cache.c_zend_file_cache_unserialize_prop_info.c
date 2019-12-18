#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * doc_comment; int /*<<< orphan*/ * name; struct TYPE_5__* ce; } ;
typedef  TYPE_1__ zend_property_info ;
typedef  int /*<<< orphan*/  zend_persistent_script ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UNSERIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

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
			zend_file_cache_unserialize_type(&prop->type, script, buf);
		}
	}
}