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
struct TYPE_6__ {char* key; } ;
typedef  TYPE_1__ JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  append_node (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void append_member(JsonNode *object, char *key, JsonNode *value)
{
	value->key = key;
	append_node(object, value);
}