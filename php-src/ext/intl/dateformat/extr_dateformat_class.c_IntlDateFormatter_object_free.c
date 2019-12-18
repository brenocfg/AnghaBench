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
struct TYPE_3__ {int /*<<< orphan*/  datef_data; scalar_t__ requested_locale; int /*<<< orphan*/  zo; } ;
typedef  TYPE_1__ IntlDateFormatter_object ;

/* Variables and functions */
 int /*<<< orphan*/  dateformat_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (scalar_t__) ; 
 TYPE_1__* php_intl_dateformatter_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void IntlDateFormatter_object_free( zend_object *object )
{
	IntlDateFormatter_object* dfo = php_intl_dateformatter_fetch_object(object);

	zend_object_std_dtor( &dfo->zo );

	if (dfo->requested_locale) {
		efree( dfo->requested_locale );
	}

	dateformat_data_free( &dfo->datef_data );
}