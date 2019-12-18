#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  phpdbg_watchpoint_t ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ phpdbg_watch_element ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * HT_FROM_ZVP (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  PHPDBG_WATCH_ARRAY ; 
 int /*<<< orphan*/  PHPDBG_WATCH_OBJECT ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* phpdbg_add_watch_element (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  phpdbg_set_ht_watchpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

phpdbg_watch_element *phpdbg_add_ht_watch_element(zval *zv, phpdbg_watch_element *element) {
	phpdbg_watchpoint_t watch;
	HashTable *ht = HT_FROM_ZVP(zv);

	if (!ht) {
		return NULL;
	}

	element->flags |= Z_TYPE_P(zv) == IS_ARRAY ? PHPDBG_WATCH_ARRAY : PHPDBG_WATCH_OBJECT;
	phpdbg_set_ht_watchpoint(ht, &watch);
	return phpdbg_add_watch_element(&watch, element);
}