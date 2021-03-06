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
struct TYPE_6__ {scalar_t__ tag; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ JsonNode ;

/* Variables and functions */
 scalar_t__ JSON_ARRAY ; 
 int /*<<< orphan*/  append_node (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void json_append_element(JsonNode *array, JsonNode *element)
{
	assert(array->tag == JSON_ARRAY);
	assert(element->parent == NULL);
	
	append_node(array, element);
}