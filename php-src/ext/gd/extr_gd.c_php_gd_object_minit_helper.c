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
typedef  int /*<<< orphan*/  zend_object_handlers ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  get_constructor; int /*<<< orphan*/  free_obj; int /*<<< orphan*/ * clone_obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; int /*<<< orphan*/  create_object; int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ACC_FINAL ; 
 TYPE_1__* gd_image_ce ; 
 int /*<<< orphan*/  gd_image_object_methods ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_gd_image_object ; 
 int /*<<< orphan*/  php_gd_image_object_create ; 
 int /*<<< orphan*/  php_gd_image_object_free ; 
 int /*<<< orphan*/  php_gd_image_object_get_constructor ; 
 TYPE_2__ php_gd_image_object_handlers ; 
 int /*<<< orphan*/  std ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 
 TYPE_1__* zend_register_internal_class (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_gd_object_minit_helper()
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "GdImage", gd_image_object_methods);
	gd_image_ce = zend_register_internal_class(&ce);
	gd_image_ce->ce_flags |= ZEND_ACC_FINAL;
	gd_image_ce->create_object = php_gd_image_object_create;
	gd_image_ce->serialize = zend_class_serialize_deny;
	gd_image_ce->unserialize = zend_class_unserialize_deny;

	/* setting up the object handlers for the GdImage class */
	memcpy(&php_gd_image_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	php_gd_image_object_handlers.clone_obj = NULL;
	php_gd_image_object_handlers.free_obj = php_gd_image_object_free;
	php_gd_image_object_handlers.get_constructor = php_gd_image_object_get_constructor;
	php_gd_image_object_handlers.offset = XtOffsetOf(php_gd_image_object, std);
}