#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {int /*<<< orphan*/ * handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/ * typeinfo; TYPE_2__ zo; int /*<<< orphan*/ * ce; int /*<<< orphan*/  code_page; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_com_initialize () ; 
 int /*<<< orphan*/  php_com_object_handlers ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_2__*,int /*<<< orphan*/ *) ; 

zend_object* php_com_object_new(zend_class_entry *ce)
{
	php_com_dotnet_object *obj;

	php_com_initialize();
	obj = emalloc(sizeof(*obj));
	memset(obj, 0, sizeof(*obj));

	VariantInit(&obj->v);
	obj->code_page = CP_ACP;
	obj->ce = ce;

	zend_object_std_init(&obj->zo, ce);
	obj->zo.handlers = &php_com_object_handlers;

	obj->typeinfo = NULL;

	return (zend_object*)obj;
}