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
struct TYPE_5__ {TYPE_2__* head; } ;
struct TYPE_6__ {scalar_t__ tag; TYPE_1__ children; } ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
 scalar_t__ JSON_ARRAY ; 
 scalar_t__ JSON_OBJECT ; 

JsonNode *json_first_child(const JsonNode *node)
{
	if (node != NULL && (node->tag == JSON_ARRAY || node->tag == JSON_OBJECT))
		return node->children.head;
	return NULL;
}