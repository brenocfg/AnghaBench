#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * doc_comment; int /*<<< orphan*/ * name; struct TYPE_6__* ce; } ;
typedef  TYPE_1__ zend_property_info ;
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  zend_file_cache_metainfo ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SERIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  SERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  SERIALIZE_STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_serialize_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_serialize_prop_info(zval                     *zv,
                                                zend_persistent_script   *script,
                                                zend_file_cache_metainfo *info,
                                                void                     *buf)
{
	if (!IS_SERIALIZED(Z_PTR_P(zv))) {
		zend_property_info *prop;

		SERIALIZE_PTR(Z_PTR_P(zv));
		prop = Z_PTR_P(zv);
		UNSERIALIZE_PTR(prop);

		ZEND_ASSERT(prop->ce != NULL && prop->name != NULL);
		if (!IS_SERIALIZED(prop->ce)) {
			SERIALIZE_PTR(prop->ce);
			SERIALIZE_STR(prop->name);
			if (prop->doc_comment) {
				SERIALIZE_STR(prop->doc_comment);
			}
			zend_file_cache_serialize_type(&prop->type, script, info, buf);
		}
	}
}