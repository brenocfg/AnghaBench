#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/ * currentkey; int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ ResourceBundle_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resourcebundle_iterator_invalidate( zend_object_iterator *iter )
{
	ResourceBundle_iterator *iterator = (ResourceBundle_iterator *) iter;

	if (!Z_ISUNDEF(iterator->current)) {
		zval_ptr_dtor( &iterator->current );
		ZVAL_UNDEF(&iterator->current);
	}
	if (iterator->currentkey) {
		efree( iterator->currentkey );
		iterator->currentkey = NULL;
	}
}