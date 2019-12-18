#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_8__ {TYPE_1__ zo; int /*<<< orphan*/  mf_data; } ;
typedef  TYPE_2__ MessageFormatter_object ;

/* Variables and functions */
 int /*<<< orphan*/  MessageFormatter_handlers ; 
 int /*<<< orphan*/  msgformat_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_object_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

zend_object *MessageFormatter_object_create(zend_class_entry *ce)
{
	MessageFormatter_object*     intern;

	intern = zend_object_alloc(sizeof(MessageFormatter_object), ce);
	msgformat_data_init( &intern->mf_data );
	zend_object_std_init( &intern->zo, ce );
	object_properties_init(&intern->zo, ce);

	intern->zo.handlers = &MessageFormatter_handlers;

	return &intern->zo;
}