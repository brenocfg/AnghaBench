#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  zstr; int /*<<< orphan*/  zchildren; int /*<<< orphan*/  zcache; } ;
struct TYPE_12__ {TYPE_3__ caching; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {int /*<<< orphan*/  zobject; int /*<<< orphan*/  ce; } ;
struct TYPE_13__ {scalar_t__ dit_type; TYPE_4__ u; TYPE_2__ current; TYPE_1__ inner; } ;
typedef  TYPE_5__ spl_dual_it_object ;

/* Variables and functions */
 int CIT_CALL_TOSTRING ; 
 int CIT_CATCH_GET_CHILD ; 
 int CIT_FULL_CACHE ; 
 int CIT_PUBLIC ; 
 int CIT_TOSTRING_USE_INNER ; 
 int CIT_VALID ; 
 scalar_t__ DIT_RecursiveCachingIterator ; 
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_set_zval_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  spl_ce_RecursiveCachingIterator ; 
 scalar_t__ spl_dual_it_fetch (TYPE_5__*,int) ; 
 int /*<<< orphan*/  spl_dual_it_next (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_instantiate_arg_ex2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_call_method_with_0_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_clear_exception () ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 
 int zend_make_printable_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void spl_caching_it_next(spl_dual_it_object *intern)
{
	if (spl_dual_it_fetch(intern, 1) == SUCCESS) {
		intern->u.caching.flags |= CIT_VALID;
		/* Full cache ? */
		if (intern->u.caching.flags & CIT_FULL_CACHE) {
			zval *key = &intern->current.key;
			zval *data = &intern->current.data;

			ZVAL_DEREF(data);
			Z_TRY_ADDREF_P(data);
			array_set_zval_key(Z_ARRVAL(intern->u.caching.zcache), key, data);
			zval_ptr_dtor(data);
		}
		/* Recursion ? */
		if (intern->dit_type == DIT_RecursiveCachingIterator) {
			zval retval, zchildren, zflags;
			zend_call_method_with_0_params(Z_OBJ(intern->inner.zobject), intern->inner.ce, NULL, "haschildren", &retval);
			if (EG(exception)) {
				zval_ptr_dtor(&retval);
				if (intern->u.caching.flags & CIT_CATCH_GET_CHILD) {
					zend_clear_exception();
				} else {
					return;
				}
			} else {
				if (zend_is_true(&retval)) {
					zend_call_method_with_0_params(Z_OBJ(intern->inner.zobject), intern->inner.ce, NULL, "getchildren", &zchildren);
					if (EG(exception)) {
						zval_ptr_dtor(&zchildren);
						if (intern->u.caching.flags & CIT_CATCH_GET_CHILD) {
							zend_clear_exception();
						} else {
							zval_ptr_dtor(&retval);
							return;
						}
					} else {
						ZVAL_LONG(&zflags, intern->u.caching.flags & CIT_PUBLIC);
						spl_instantiate_arg_ex2(spl_ce_RecursiveCachingIterator, &intern->u.caching.zchildren, &zchildren, &zflags);
						zval_ptr_dtor(&zchildren);
					}
				}
				zval_ptr_dtor(&retval);
				if (EG(exception)) {
					if (intern->u.caching.flags & CIT_CATCH_GET_CHILD) {
						zend_clear_exception();
					} else {
						return;
					}
				}
			}
		}
		if (intern->u.caching.flags & (CIT_TOSTRING_USE_INNER|CIT_CALL_TOSTRING)) {
			int  use_copy;
			zval expr_copy;
			if (intern->u.caching.flags & CIT_TOSTRING_USE_INNER) {
				ZVAL_COPY_VALUE(&intern->u.caching.zstr, &intern->inner.zobject);
			} else {
				ZVAL_COPY_VALUE(&intern->u.caching.zstr, &intern->current.data);
			}
			use_copy = zend_make_printable_zval(&intern->u.caching.zstr, &expr_copy);
			if (use_copy) {
				ZVAL_COPY_VALUE(&intern->u.caching.zstr, &expr_copy);
			} else {
				Z_TRY_ADDREF(intern->u.caching.zstr);
			}
		}
		spl_dual_it_next(intern, 0);
	} else {
		intern->u.caching.flags &= ~CIT_VALID;
	}
}