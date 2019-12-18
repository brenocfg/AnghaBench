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
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  zend_file_cache_metainfo ;
struct TYPE_6__ {scalar_t__ doc_comment; int /*<<< orphan*/  value; struct TYPE_6__* ce; } ;
typedef  TYPE_1__ zend_class_constant ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SERIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  SERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  SERIALIZE_STR (scalar_t__) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_serialize_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_serialize_class_constant(zval                     *zv,
                                                     zend_persistent_script   *script,
                                                     zend_file_cache_metainfo *info,
                                                     void                     *buf)
{
	if (!IS_SERIALIZED(Z_PTR_P(zv))) {
		zend_class_constant *c;

		SERIALIZE_PTR(Z_PTR_P(zv));
		c = Z_PTR_P(zv);
		UNSERIALIZE_PTR(c);

		ZEND_ASSERT(c->ce != NULL);
		if (!IS_SERIALIZED(c->ce)) {
			SERIALIZE_PTR(c->ce);

			zend_file_cache_serialize_zval(&c->value, script, info, buf);

			if (c->doc_comment) {
				SERIALIZE_STR(c->doc_comment);
			}
		}
	}
}