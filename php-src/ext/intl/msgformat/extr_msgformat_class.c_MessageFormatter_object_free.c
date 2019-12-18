#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  mf_data; int /*<<< orphan*/  zo; } ;
typedef  TYPE_1__ MessageFormatter_object ;

/* Variables and functions */
 int /*<<< orphan*/  msgformat_data_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* php_intl_messageformatter_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void MessageFormatter_object_free( zend_object *object )
{
	MessageFormatter_object* mfo = php_intl_messageformatter_fetch_object(object);

	zend_object_std_dtor( &mfo->zo );

	msgformat_data_free( &mfo->mf_data );
}