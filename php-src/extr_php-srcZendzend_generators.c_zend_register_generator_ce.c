#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_handlers ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_7__ {int /*<<< orphan*/  get_constructor; int /*<<< orphan*/ * clone_obj; int /*<<< orphan*/  get_gc; int /*<<< orphan*/  dtor_obj; int /*<<< orphan*/  free_obj; } ;
struct TYPE_6__ {int /*<<< orphan*/  get_iterator; int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; int /*<<< orphan*/  create_object; int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ACC_FINAL ; 
 int /*<<< orphan*/ * generator_functions ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_ce_ClosedGeneratorException ; 
 int /*<<< orphan*/  zend_ce_exception ; 
 TYPE_1__* zend_ce_generator ; 
 int /*<<< orphan*/  zend_ce_iterator ; 
 int /*<<< orphan*/  zend_class_implements (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 
 int /*<<< orphan*/  zend_generator_create ; 
 int /*<<< orphan*/  zend_generator_dtor_storage ; 
 int /*<<< orphan*/  zend_generator_free_storage ; 
 int /*<<< orphan*/  zend_generator_get_constructor ; 
 int /*<<< orphan*/  zend_generator_get_gc ; 
 int /*<<< orphan*/  zend_generator_get_iterator ; 
 TYPE_2__ zend_generator_handlers ; 
 TYPE_1__* zend_register_internal_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_register_internal_class_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zend_register_generator_ce(void) /* {{{ */
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Generator", generator_functions);
	zend_ce_generator = zend_register_internal_class(&ce);
	zend_ce_generator->ce_flags |= ZEND_ACC_FINAL;
	zend_ce_generator->create_object = zend_generator_create;
	zend_ce_generator->serialize = zend_class_serialize_deny;
	zend_ce_generator->unserialize = zend_class_unserialize_deny;

	/* get_iterator has to be assigned *after* implementing the inferface */
	zend_class_implements(zend_ce_generator, 1, zend_ce_iterator);
	zend_ce_generator->get_iterator = zend_generator_get_iterator;

	memcpy(&zend_generator_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	zend_generator_handlers.free_obj = zend_generator_free_storage;
	zend_generator_handlers.dtor_obj = zend_generator_dtor_storage;
	zend_generator_handlers.get_gc = zend_generator_get_gc;
	zend_generator_handlers.clone_obj = NULL;
	zend_generator_handlers.get_constructor = zend_generator_get_constructor;

	INIT_CLASS_ENTRY(ce, "ClosedGeneratorException", NULL);
	zend_ce_ClosedGeneratorException = zend_register_internal_class_ex(&ce, zend_ce_exception);
}