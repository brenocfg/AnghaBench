#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ spl_ptr_llist_element ;
struct TYPE_4__ {TYPE_1__* traverse_pointer; } ;
typedef  TYPE_2__ spl_dllist_it ;

/* Variables and functions */
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *spl_dllist_it_get_current_data(zend_object_iterator *iter) /* {{{ */
{
	spl_dllist_it         *iterator = (spl_dllist_it *)iter;
	spl_ptr_llist_element *element  = iterator->traverse_pointer;

	if (element == NULL || Z_ISUNDEF(element->data)) {
		return NULL;
	}

	return &element->data;
}