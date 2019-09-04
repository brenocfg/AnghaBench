#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; TYPE_2__* parent; int /*<<< orphan*/  str; TYPE_1__* watch; struct TYPE_10__* child; } ;
typedef  TYPE_3__ phpdbg_watch_element ;
struct TYPE_9__ {int flags; int /*<<< orphan*/ * child; int /*<<< orphan*/  child_container; } ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 int PHPDBG_WATCH_ARRAY ; 
 int PHPDBG_WATCH_IMPLICIT ; 
 int PHPDBG_WATCH_OBJECT ; 
 int PHPDBG_WATCH_RECURSIVE ; 
 int PHPDBG_WATCH_RECURSIVE_ROOT ; 
 int PHPDBG_WATCH_SIMPLE ; 
 scalar_t__ WATCH_ON_BUCKET ; 
 scalar_t__ WATCH_ON_ZVAL ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  phpdbg_free_watch_element (TYPE_3__*) ; 
 int /*<<< orphan*/  phpdbg_queue_element_for_recreation (TYPE_3__*) ; 
 int /*<<< orphan*/  phpdbg_remove_watch_element_recursively (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void phpdbg_update_watch_element_watch(phpdbg_watch_element *element) {
	if (element->flags & PHPDBG_WATCH_IMPLICIT) {
		phpdbg_watch_element *child = element->child;
		while (child->flags & PHPDBG_WATCH_IMPLICIT) {
			child = child->child;
		}

		ZEND_ASSERT(element->watch->type == WATCH_ON_ZVAL || element->watch->type == WATCH_ON_BUCKET);
		phpdbg_queue_element_for_recreation(element);
	} else if (element->flags & (PHPDBG_WATCH_RECURSIVE_ROOT | PHPDBG_WATCH_SIMPLE)) {
		phpdbg_queue_element_for_recreation(element);
	} else if (element->flags & PHPDBG_WATCH_RECURSIVE) {
		phpdbg_remove_watch_element_recursively(element);
		if (element->parent->flags & (PHPDBG_WATCH_OBJECT | PHPDBG_WATCH_ARRAY)) {
			zend_hash_del(&element->parent->child_container, element->str);
		} else {
			element->parent->child = NULL;
		}
		phpdbg_free_watch_element(element);
	}
}