#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* free; } ;
struct TYPE_5__ {TYPE_2__* child_list; TYPE_2__* module_list; struct TYPE_5__* pattern_bytes; struct TYPE_5__* variant_bool_array; } ;
typedef  void* RListFree ;
typedef  TYPE_1__ RFlirtNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ module_free ; 
 int /*<<< orphan*/  r_list_free (TYPE_2__*) ; 

__attribute__((used)) static void node_free(RFlirtNode *node) {
	if (!node) {
		return;
	}
	free (node->variant_bool_array);
	free (node->pattern_bytes);
	if (node->module_list) {
		node->module_list->free = (RListFree)module_free;
		r_list_free (node->module_list);
	}
	if (node->child_list) {
		node->child_list->free = (RListFree) node_free;
		r_list_free (node->child_list);
	}
	free (node);
}