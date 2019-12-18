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
struct TYPE_4__ {scalar_t__ name_in_parent; scalar_t__ str; } ;
typedef  TYPE_1__ phpdbg_watch_element ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_string_release (scalar_t__) ; 

void phpdbg_free_watch_element(phpdbg_watch_element *element) {
	zend_string_release(element->str);
	if (element->name_in_parent) {
		zend_string_release(element->name_in_parent);
	}
	efree(element);
}