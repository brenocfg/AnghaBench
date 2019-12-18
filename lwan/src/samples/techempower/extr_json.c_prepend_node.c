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
struct TYPE_5__ {TYPE_2__* head; TYPE_2__* tail; } ;
struct TYPE_6__ {TYPE_1__ children; struct TYPE_6__* prev; struct TYPE_6__* next; struct TYPE_6__* parent; } ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */

__attribute__((used)) static void prepend_node(JsonNode *parent, JsonNode *child)
{
	child->parent = parent;
	child->prev = NULL;
	child->next = parent->children.head;
	
	if (parent->children.head != NULL)
		parent->children.head->prev = child;
	else
		parent->children.tail = child;
	parent->children.head = child;
}