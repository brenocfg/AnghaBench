#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* tail; TYPE_3__* head; } ;
struct TYPE_9__ {int /*<<< orphan*/ * key; TYPE_3__* next; TYPE_2__* prev; struct TYPE_9__* parent; TYPE_1__ children; } ;
struct TYPE_8__ {TYPE_2__* prev; } ;
struct TYPE_7__ {TYPE_3__* next; } ;
typedef  TYPE_4__ JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void json_remove_from_parent(JsonNode *node)
{
	JsonNode *parent = node->parent;
	
	if (parent != NULL) {
		if (node->prev != NULL)
			node->prev->next = node->next;
		else
			parent->children.head = node->next;
		if (node->next != NULL)
			node->next->prev = node->prev;
		else
			parent->children.tail = node->prev;
		
		free(node->key);
		
		node->parent = NULL;
		node->prev = node->next = NULL;
		node->key = NULL;
	}
}