#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zchildren; int /*<<< orphan*/  zstr; } ;
struct TYPE_13__ {TYPE_4__ caching; } ;
struct TYPE_11__ {int /*<<< orphan*/  key; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_7__* iterator; } ;
struct TYPE_14__ {scalar_t__ dit_type; TYPE_5__ u; TYPE_3__ current; TYPE_2__ inner; } ;
typedef  TYPE_6__ spl_dual_it_object ;
struct TYPE_15__ {TYPE_1__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* invalidate_current ) (TYPE_7__*) ;} ;

/* Variables and functions */
 scalar_t__ DIT_CachingIterator ; 
 scalar_t__ DIT_RecursiveCachingIterator ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void spl_dual_it_free(spl_dual_it_object *intern)
{
	if (intern->inner.iterator && intern->inner.iterator->funcs->invalidate_current) {
		intern->inner.iterator->funcs->invalidate_current(intern->inner.iterator);
	}
	if (Z_TYPE(intern->current.data) != IS_UNDEF) {
		zval_ptr_dtor(&intern->current.data);
		ZVAL_UNDEF(&intern->current.data);
	}
	if (Z_TYPE(intern->current.key) != IS_UNDEF) {
		zval_ptr_dtor(&intern->current.key);
		ZVAL_UNDEF(&intern->current.key);
	}
	if (intern->dit_type == DIT_CachingIterator || intern->dit_type == DIT_RecursiveCachingIterator) {
		if (Z_TYPE(intern->u.caching.zstr) != IS_UNDEF) {
			zval_ptr_dtor(&intern->u.caching.zstr);
			ZVAL_UNDEF(&intern->u.caching.zstr);
		}
		if (Z_TYPE(intern->u.caching.zchildren) != IS_UNDEF) {
			zval_ptr_dtor(&intern->u.caching.zchildren);
			ZVAL_UNDEF(&intern->u.caching.zchildren);
		}
	}
}