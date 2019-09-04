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
typedef  int /*<<< orphan*/  zend_persistent_script ;
struct TYPE_5__ {scalar_t__ doc_comment; int /*<<< orphan*/  value; struct TYPE_5__* ce; } ;
typedef  TYPE_1__ zend_class_constant ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UNSERIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_STR (scalar_t__) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_unserialize_class_constant(zval                    *zv,
                                                       zend_persistent_script  *script,
                                                       void                    *buf)
{
	if (!IS_UNSERIALIZED(Z_PTR_P(zv))) {
		zend_class_constant *c;

		UNSERIALIZE_PTR(Z_PTR_P(zv));
		c = Z_PTR_P(zv);

		ZEND_ASSERT(c->ce != NULL);
		if (!IS_UNSERIALIZED(c->ce)) {
			UNSERIALIZE_PTR(c->ce);

			zend_file_cache_unserialize_zval(&c->value, script, buf);

			if (c->doc_comment) {
				UNSERIALIZE_STR(c->doc_comment);
			}
		}
	}
}