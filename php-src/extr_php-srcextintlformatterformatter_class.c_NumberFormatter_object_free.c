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
struct TYPE_3__ {int /*<<< orphan*/  nf_data; int /*<<< orphan*/  zo; } ;
typedef  TYPE_1__ NumberFormatter_object ;

/* Variables and functions */
 int /*<<< orphan*/  formatter_data_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* php_intl_number_format_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void NumberFormatter_object_free( zend_object *object )
{
	NumberFormatter_object* nfo = php_intl_number_format_fetch_object(object);

	zend_object_std_dtor( &nfo->zo );

	formatter_data_free( &nfo->nf_data );
}