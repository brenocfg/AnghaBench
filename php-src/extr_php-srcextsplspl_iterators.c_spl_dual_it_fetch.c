#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_12__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  key; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_5__* iterator; } ;
struct TYPE_13__ {TYPE_3__ current; TYPE_2__ inner; } ;
typedef  TYPE_4__ spl_dual_it_object ;
struct TYPE_14__ {TYPE_1__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* get_current_key ) (TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* get_current_data ) (TYPE_5__*) ;} ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  spl_dual_it_free (TYPE_4__*) ; 
 scalar_t__ spl_dual_it_valid (TYPE_4__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int spl_dual_it_fetch(spl_dual_it_object *intern, int check_more)
{
	zval *data;

	spl_dual_it_free(intern);
	if (!check_more || spl_dual_it_valid(intern) == SUCCESS) {
		data = intern->inner.iterator->funcs->get_current_data(intern->inner.iterator);
		if (data) {
			ZVAL_COPY(&intern->current.data, data);
		}

		if (intern->inner.iterator->funcs->get_current_key) {
			intern->inner.iterator->funcs->get_current_key(intern->inner.iterator, &intern->current.key);
			if (EG(exception)) {
				zval_ptr_dtor(&intern->current.key);
				ZVAL_UNDEF(&intern->current.key);
			}
		} else {
			ZVAL_LONG(&intern->current.key, intern->current.pos);
		}
		return EG(exception) ? FAILURE : SUCCESS;
	}
	return FAILURE;
}