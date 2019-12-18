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
typedef  int /*<<< orphan*/  spl_ptr_llist_element ;
struct TYPE_2__ {int /*<<< orphan*/ * traverse_pointer; } ;
typedef  TYPE_1__ spl_dllist_it ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 

__attribute__((used)) static int spl_dllist_it_valid(zend_object_iterator *iter) /* {{{ */
{
	spl_dllist_it         *iterator = (spl_dllist_it *)iter;
	spl_ptr_llist_element *element  = iterator->traverse_pointer;

	return (element != NULL ? SUCCESS : FAILURE);
}