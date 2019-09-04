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
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {int /*<<< orphan*/  create_object; } ;
struct TYPE_5__ {int /*<<< orphan*/  create_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY_EX (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* IntlException_ce_ptr ; 
 TYPE_2__* zend_ce_exception ; 
 TYPE_1__* zend_register_internal_class_ex (int /*<<< orphan*/ *,TYPE_2__*) ; 

void intl_register_IntlException_class( void )
{
	zend_class_entry ce;

	/* Create and register 'IntlException' class. */
	INIT_CLASS_ENTRY_EX( ce, "IntlException", sizeof( "IntlException" ) - 1, NULL );
	IntlException_ce_ptr = zend_register_internal_class_ex( &ce,
		zend_ce_exception );
	IntlException_ce_ptr->create_object = zend_ce_exception->create_object;
}