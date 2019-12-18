#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {scalar_t__ ce; } ;
typedef  TYPE_1__ zend_object ;
struct TYPE_13__ {int /*<<< orphan*/ * handlers; } ;
struct TYPE_11__ {int dimensions; TYPE_4__ std; int /*<<< orphan*/ * indices; TYPE_3__* obj; } ;
typedef  TYPE_2__ php_com_saproxy ;
struct TYPE_12__ {int /*<<< orphan*/  zo; } ;
typedef  TYPE_3__ php_com_dotnet_object ;

/* Variables and functions */
 int /*<<< orphan*/  GC_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DUP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  clone_indices (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* ecalloc (int,int) ; 
 scalar_t__ php_com_saproxy_class_entry ; 
 int /*<<< orphan*/  php_com_saproxy_handlers ; 
 int /*<<< orphan*/ * safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_4__*,scalar_t__) ; 

int php_com_saproxy_create(zend_object *com_object, zval *proxy_out, zval *index)
{
	php_com_saproxy *proxy, *rel = NULL;

	proxy = ecalloc(1, sizeof(*proxy));
	proxy->dimensions = 1;

	if (com_object->ce == php_com_saproxy_class_entry) {
		rel = (php_com_saproxy*) com_object;
		proxy->obj = rel->obj;
		proxy->dimensions += rel->dimensions;
	} else {
		proxy->obj = (php_com_dotnet_object*) com_object;
	}

	GC_ADDREF(&proxy->obj->zo);
	proxy->indices = safe_emalloc(proxy->dimensions, sizeof(zval *), 0);

	if (rel) {
		clone_indices(proxy, rel, rel->dimensions);
	}

	ZVAL_DUP(&proxy->indices[proxy->dimensions-1], index);

	zend_object_std_init(&proxy->std, php_com_saproxy_class_entry);
	proxy->std.handlers = &php_com_saproxy_handlers;
	ZVAL_OBJ(proxy_out, &proxy->std);

	return 1;
}