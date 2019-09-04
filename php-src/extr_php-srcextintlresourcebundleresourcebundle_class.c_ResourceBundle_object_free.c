#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/  zend; scalar_t__ child; scalar_t__ me; } ;
typedef  TYPE_1__ ResourceBundle_object ;

/* Variables and functions */
 int /*<<< orphan*/  INTL_DATA_ERROR_P (TYPE_1__*) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ ) ; 
 TYPE_1__* php_intl_resourcebundle_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ures_close (scalar_t__) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ResourceBundle_object_free( zend_object *object )
{
	ResourceBundle_object *rb = php_intl_resourcebundle_fetch_object(object);

	// only free local errors
	intl_error_reset( INTL_DATA_ERROR_P(rb) );

	if (rb->me) {
		ures_close( rb->me );
	}
	if (rb->child) {
		ures_close( rb->child );
	}

	zend_object_std_dtor( &rb->zend );
}