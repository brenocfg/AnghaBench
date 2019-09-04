#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int refcount; int /*<<< orphan*/  res; int /*<<< orphan*/  object; int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/  engine_thread; } ;
typedef  TYPE_1__ php_dispatchex ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 TYPE_5__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_RES_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le_dispatch ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_dispatch_vtbl ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_list_insert (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static php_dispatchex *disp_constructor(zval *object)
{
	php_dispatchex *disp = (php_dispatchex*)CoTaskMemAlloc(sizeof(php_dispatchex));
	zval *tmp;

	trace("constructing a COM wrapper for PHP object %p (%s)\n", object, Z_OBJCE_P(object)->name);

	if (disp == NULL)
		return NULL;

	memset(disp, 0, sizeof(php_dispatchex));

	disp->engine_thread = GetCurrentThreadId();
	disp->lpVtbl = &php_dispatch_vtbl;
	disp->refcount = 1;


	if (object) {
		ZVAL_COPY(&disp->object, object);
	} else {
		ZVAL_UNDEF(&disp->object);
	}

	tmp = zend_list_insert(disp, le_dispatch);
	disp->res = Z_RES_P(tmp);

	return disp;
}