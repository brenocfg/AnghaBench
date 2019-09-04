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
struct TYPE_5__ {TYPE_2__* tail; TYPE_2__* head; } ;
struct TYPE_6__ {TYPE_1__ children; struct TYPE_6__* next; struct TYPE_6__* prev; struct TYPE_6__* parent; } ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */

__attribute__((used)) static void append_node(JsonNode *parent, JsonNode *child)
{
	child->parent = parent;
	child->prev = parent->children.tail;
	child->next = NULL;
	
	if (parent->children.tail != NULL)
		parent->children.tail->next = child;
	else
		parent->children.head = child;
	parent->children.tail = child;
}