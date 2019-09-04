#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
struct TYPE_7__ {int flags; struct TYPE_7__* parent; TYPE_2__* watch; } ;
typedef  TYPE_3__ phpdbg_watch_element ;
struct TYPE_5__ {void* ptr; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;

/* Variables and functions */
 int PHPDBG_WATCH_RECURSIVE_ROOT ; 

zend_bool phpdbg_is_recursively_watched(void *ptr, phpdbg_watch_element *element) {
	phpdbg_watch_element *next = element;
	do {
		element = next;
		if (element->watch->addr.ptr == ptr) {
			return 1;
		}
		next = element->parent;
	} while (!(element->flags & PHPDBG_WATCH_RECURSIVE_ROOT));

	return 0;
}