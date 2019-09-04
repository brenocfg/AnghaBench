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
struct TYPE_6__ {TYPE_2__* head; } ;
struct TYPE_7__ {int tag; struct TYPE_7__* next; TYPE_1__ children; struct TYPE_7__* string_; } ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
#define  JSON_ARRAY 130 
#define  JSON_OBJECT 129 
#define  JSON_STRING 128 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  json_remove_from_parent (TYPE_2__*) ; 

void json_delete(JsonNode *node)
{
	if (node != NULL) {
		json_remove_from_parent(node);
		
		switch (node->tag) {
			case JSON_STRING:
				free(node->string_);
				break;
			case JSON_ARRAY:
			case JSON_OBJECT:
			{
				JsonNode *child, *next;
				for (child = node->children.head; child != NULL; child = next) {
					next = child->next;
					json_delete(child);
				}
				break;
			}
			default:;
		}
		
		free(node);
	}
}