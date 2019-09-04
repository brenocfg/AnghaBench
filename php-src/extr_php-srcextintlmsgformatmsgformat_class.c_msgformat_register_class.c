#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  create_object; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_7__ {int /*<<< orphan*/  free_obj; int /*<<< orphan*/  clone_obj; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (TYPE_1__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageFormatter_ce_ptr ; 
 int /*<<< orphan*/  MessageFormatter_class_functions ; 
 TYPE_3__ MessageFormatter_handlers ; 
 int /*<<< orphan*/  MessageFormatter_object ; 
 int /*<<< orphan*/  MessageFormatter_object_clone ; 
 int /*<<< orphan*/  MessageFormatter_object_create ; 
 int /*<<< orphan*/  MessageFormatter_object_free ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_register_internal_class (TYPE_1__*) ; 
 int /*<<< orphan*/  zo ; 

void msgformat_register_class( void )
{
	zend_class_entry ce;

	/* Create and register 'MessageFormatter' class. */
	INIT_CLASS_ENTRY( ce, "MessageFormatter", MessageFormatter_class_functions );
	ce.create_object = MessageFormatter_object_create;
	MessageFormatter_ce_ptr = zend_register_internal_class( &ce );

	memcpy(&MessageFormatter_handlers, &std_object_handlers,
		sizeof MessageFormatter_handlers);
	MessageFormatter_handlers.offset = XtOffsetOf(MessageFormatter_object, zo);
	MessageFormatter_handlers.clone_obj = MessageFormatter_object_clone;
	MessageFormatter_handlers.free_obj = MessageFormatter_object_free;
}