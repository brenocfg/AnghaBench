#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {TYPE_6__* function_handler; } ;
struct TYPE_9__ {TYPE_2__ fcc; int /*<<< orphan*/  callback; } ;
typedef  TYPE_3__ zend_ffi_callback_data ;
struct TYPE_7__ {int fn_flags; } ;
struct TYPE_10__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_RELEASE (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_CLOSURE ; 
 int /*<<< orphan*/  ZEND_CLOSURE_OBJECT (TYPE_6__*) ; 
 TYPE_3__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_3__*) ; 
 int /*<<< orphan*/  ffi_closure_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_ffi_callback_hash_dtor(zval *zv) /* {{{ */
{
	zend_ffi_callback_data *callback_data = Z_PTR_P(zv);

	ffi_closure_free(callback_data->callback);
	if (callback_data->fcc.function_handler->common.fn_flags & ZEND_ACC_CLOSURE) {
		OBJ_RELEASE(ZEND_CLOSURE_OBJECT(callback_data->fcc.function_handler));
	}
	efree(callback_data);
}