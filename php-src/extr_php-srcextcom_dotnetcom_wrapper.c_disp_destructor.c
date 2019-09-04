#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ refcount; int /*<<< orphan*/  object; int /*<<< orphan*/  name_to_dispid; int /*<<< orphan*/  dispid_to_name; int /*<<< orphan*/ * res; } ;
typedef  TYPE_2__ php_dispatchex ;
struct TYPE_8__ {TYPE_1__* name; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 scalar_t__ COMG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoDisconnectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  FREE_HASHTABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ (int /*<<< orphan*/ ) ; 
 TYPE_4__* Z_OBJCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rshutdown_started ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disp_destructor(php_dispatchex *disp)
{
	/* Object store not available during request shutdown */
	if (COMG(rshutdown_started)) {
		trace("destroying COM wrapper for PHP object %p (name:unknown)\n", Z_OBJ(disp->object));
	} else {
		trace("destroying COM wrapper for PHP object %p (name:%s)\n", Z_OBJ(disp->object), Z_OBJCE(disp->object)->name->val);
	}

	disp->res = NULL;

	if (disp->refcount > 0)
		CoDisconnectObject((IUnknown*)disp, 0);

	zend_hash_destroy(disp->dispid_to_name);
	zend_hash_destroy(disp->name_to_dispid);
	FREE_HASHTABLE(disp->dispid_to_name);
	FREE_HASHTABLE(disp->name_to_dispid);

	zval_ptr_dtor(&disp->object);

	CoTaskMemFree(disp);
}