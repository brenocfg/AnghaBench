#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ idx; } ;
typedef  TYPE_1__ phpdbg_btree_result ;
struct TYPE_7__ {scalar_t__ cur; scalar_t__ end; int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ phpdbg_btree_position ;

/* Variables and functions */
 TYPE_1__* phpdbg_btree_find_closest (int /*<<< orphan*/ ,scalar_t__) ; 

phpdbg_btree_result *phpdbg_btree_next(phpdbg_btree_position *pos) {
	phpdbg_btree_result *result = phpdbg_btree_find_closest(pos->tree, pos->cur);

	if (result == NULL || result->idx < pos->end) {
		return NULL;
	}

	pos->cur = result->idx - 1;

	return result;
}