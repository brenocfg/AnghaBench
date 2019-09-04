#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ (* compare ) (int /*<<< orphan*/ ,void*) ;int list_level; int /*<<< orphan*/  size; TYPE_1__* head; } ;
struct TYPE_9__ {struct TYPE_9__** forward; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RSkipListNode ;
typedef  TYPE_2__ RSkipList ;

/* Variables and functions */
 int /*<<< orphan*/  SKIPLIST_MAX_DEPTH ; 
 TYPE_1__* find_insertpoint (TYPE_2__*,void*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  r_skiplist_node_free (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool delete_element(RSkipList* list, void* data, bool by_data) {
	int i;
	RSkipListNode *update[SKIPLIST_MAX_DEPTH + 1], *x;

	// locate delete points in the lists of all levels
	x = find_insertpoint (list, data, update, by_data);
	// do nothing if the element is not present in the list
	if (x == list->head || list->compare(x->data, data) != 0) {
		return false;
	}

	// update forward links for all `update` points,
	// by removing the element from the list in each level
	for (i = 0; i <= list->list_level; i++) {
		if (update[i]->forward[i] != x) {
			break;
		}
		update[i]->forward[i] = x->forward[i];
	}
	r_skiplist_node_free (list, x);

	// update the level of the list
	while ((list->list_level > 0) &&
		(list->head->forward[list->list_level] == list->head)) {
		list->list_level--;
	}
	list->size--;
	return true;
}