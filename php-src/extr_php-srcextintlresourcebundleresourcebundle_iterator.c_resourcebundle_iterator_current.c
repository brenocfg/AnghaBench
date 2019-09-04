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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ ResourceBundle_iterator ;

/* Variables and functions */
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resourcebundle_iterator_read (TYPE_1__*) ; 

__attribute__((used)) static zval *resourcebundle_iterator_current( zend_object_iterator *iter )
{
	ResourceBundle_iterator *iterator = (ResourceBundle_iterator *) iter;
	if (Z_ISUNDEF(iterator->current)) {
		resourcebundle_iterator_read( iterator);
	}
	return &iterator->current;
}