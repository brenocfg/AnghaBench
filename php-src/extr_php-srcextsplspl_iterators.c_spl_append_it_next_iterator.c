#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_16__ {TYPE_6__* ce; int /*<<< orphan*/ * iterator; int /*<<< orphan*/  zobject; } ;
struct TYPE_14__ {TYPE_7__* iterator; } ;
struct TYPE_15__ {TYPE_2__ append; } ;
struct TYPE_17__ {TYPE_4__ inner; TYPE_3__ u; } ;
typedef  TYPE_5__ spl_dual_it_object ;
struct TYPE_19__ {TYPE_1__* funcs; } ;
struct TYPE_18__ {int /*<<< orphan*/ * (* get_iterator ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {scalar_t__ (* valid ) (TYPE_7__*) ;int /*<<< orphan*/ * (* get_current_data ) (TYPE_7__*) ;} ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 TYPE_6__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_dual_it_free (TYPE_5__*) ; 
 int /*<<< orphan*/  spl_dual_it_rewind (TYPE_5__*) ; 
 scalar_t__ stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_7__*) ; 
 int /*<<< orphan*/ * stub3 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_iterator_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

int spl_append_it_next_iterator(spl_dual_it_object *intern) /* {{{*/
{
	spl_dual_it_free(intern);

	if (!Z_ISUNDEF(intern->inner.zobject)) {
		zval_ptr_dtor(&intern->inner.zobject);
		ZVAL_UNDEF(&intern->inner.zobject);
		intern->inner.ce = NULL;
		if (intern->inner.iterator) {
			zend_iterator_dtor(intern->inner.iterator);
			intern->inner.iterator = NULL;
		}
	}
	if (intern->u.append.iterator->funcs->valid(intern->u.append.iterator) == SUCCESS) {
		zval *it;

		it  = intern->u.append.iterator->funcs->get_current_data(intern->u.append.iterator);
		ZVAL_COPY(&intern->inner.zobject, it);
		intern->inner.ce = Z_OBJCE_P(it);
		intern->inner.iterator = intern->inner.ce->get_iterator(intern->inner.ce, it, 0);
		spl_dual_it_rewind(intern);
		return SUCCESS;
	} else {
		return FAILURE;
	}
}