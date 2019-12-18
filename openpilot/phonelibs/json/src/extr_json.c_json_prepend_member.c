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
struct TYPE_6__ {scalar_t__ tag; int /*<<< orphan*/  key; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ JsonNode ;

/* Variables and functions */
 scalar_t__ JSON_OBJECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  json_strdup (char const*) ; 
 int /*<<< orphan*/  prepend_node (TYPE_1__*,TYPE_1__*) ; 

void json_prepend_member(JsonNode *object, const char *key, JsonNode *value)
{
	assert(object->tag == JSON_OBJECT);
	assert(value->parent == NULL);
	
	value->key = json_strdup(key);
	prepend_node(object, value);
}