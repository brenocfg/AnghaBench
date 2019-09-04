#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_14__ {scalar_t__ regex; scalar_t__ pce; } ;
struct TYPE_13__ {int /*<<< orphan*/  zcache; } ;
struct TYPE_12__ {int /*<<< orphan*/  zarrayit; int /*<<< orphan*/  iterator; } ;
struct TYPE_15__ {TYPE_8__* cbfilter; TYPE_4__ regex; TYPE_3__ caching; TYPE_2__ append; } ;
struct TYPE_11__ {int /*<<< orphan*/  zobject; } ;
struct TYPE_17__ {scalar_t__ dit_type; int /*<<< orphan*/  std; TYPE_5__ u; TYPE_1__ inner; } ;
typedef  TYPE_7__ spl_dual_it_object ;
struct TYPE_16__ {scalar_t__ object; int /*<<< orphan*/  function_name; } ;
struct TYPE_18__ {TYPE_6__ fci; } ;
typedef  TYPE_8__ _spl_cbfilter_it_intern ;

/* Variables and functions */
 scalar_t__ DIT_AppendIterator ; 
 scalar_t__ DIT_CachingIterator ; 
 scalar_t__ DIT_CallbackFilterIterator ; 
 scalar_t__ DIT_RecursiveCachingIterator ; 
 scalar_t__ DIT_RecursiveCallbackFilterIterator ; 
 scalar_t__ DIT_RecursiveRegexIterator ; 
 scalar_t__ DIT_RegexIterator ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  OBJ_RELEASE (scalar_t__) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_8__*) ; 
 int /*<<< orphan*/  php_pcre_pce_decref (scalar_t__) ; 
 TYPE_7__* spl_dual_it_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_iterator_dtor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_dual_it_free_storage(zend_object *_object)
{
	spl_dual_it_object *object = spl_dual_it_from_obj(_object);


	if (!Z_ISUNDEF(object->inner.zobject)) {
		zval_ptr_dtor(&object->inner.zobject);
	}

	if (object->dit_type == DIT_AppendIterator) {
		zend_iterator_dtor(object->u.append.iterator);
		if (Z_TYPE(object->u.append.zarrayit) != IS_UNDEF) {
			zval_ptr_dtor(&object->u.append.zarrayit);
		}
	}

	if (object->dit_type == DIT_CachingIterator || object->dit_type == DIT_RecursiveCachingIterator) {
		zval_ptr_dtor(&object->u.caching.zcache);
	}

	if (object->dit_type == DIT_RegexIterator || object->dit_type == DIT_RecursiveRegexIterator) {
		if (object->u.regex.pce) {
			php_pcre_pce_decref(object->u.regex.pce);
		}
		if (object->u.regex.regex) {
			zend_string_release_ex(object->u.regex.regex, 0);
		}
	}

	if (object->dit_type == DIT_CallbackFilterIterator || object->dit_type == DIT_RecursiveCallbackFilterIterator) {
		if (object->u.cbfilter) {
			_spl_cbfilter_it_intern *cbfilter = object->u.cbfilter;
			object->u.cbfilter = NULL;
			zval_ptr_dtor(&cbfilter->fci.function_name);
			if (cbfilter->fci.object) {
				OBJ_RELEASE(cbfilter->fci.object);
			}
			efree(cbfilter);
		}
	}

	zend_object_std_dtor(&object->std);
}