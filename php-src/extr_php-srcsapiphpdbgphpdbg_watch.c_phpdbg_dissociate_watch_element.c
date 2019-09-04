#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; struct TYPE_7__* child; } ;
typedef  TYPE_1__ phpdbg_watch_element ;

/* Variables and functions */
 int PHPDBG_WATCH_RECURSIVE ; 
 int PHPDBG_WATCH_RECURSIVE_ROOT ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  phpdbg_backup_watch_element (TYPE_1__*) ; 
 int /*<<< orphan*/  phpdbg_clean_watch_element (TYPE_1__*) ; 
 int /*<<< orphan*/  phpdbg_remove_watch_element_recursively (TYPE_1__*) ; 

void phpdbg_dissociate_watch_element(phpdbg_watch_element *element, phpdbg_watch_element *until) {
	phpdbg_watch_element *child = element;
	ZEND_ASSERT((element->flags & (PHPDBG_WATCH_RECURSIVE_ROOT | PHPDBG_WATCH_RECURSIVE)) != PHPDBG_WATCH_RECURSIVE);

	if (element->flags & PHPDBG_WATCH_RECURSIVE_ROOT) {
		phpdbg_backup_watch_element(element);
		phpdbg_remove_watch_element_recursively(element);
		return;
	}

	while (child->child != until) {
		child = child->child;
		if (child->flags & PHPDBG_WATCH_RECURSIVE_ROOT) {
			phpdbg_backup_watch_element(child);
			phpdbg_remove_watch_element_recursively(child);
			child->child = NULL;
			break;
		}
		if (child->child == NULL || (child->flags & PHPDBG_WATCH_RECURSIVE_ROOT)) {
			phpdbg_backup_watch_element(child);
		}
		phpdbg_clean_watch_element(child);
	}
	/* element needs to be removed last! */
	if (element->child == NULL) {
		phpdbg_backup_watch_element(element);
	}
	phpdbg_clean_watch_element(element);
}