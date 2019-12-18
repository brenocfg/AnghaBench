#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct descriptor_item {int /*<<< orphan*/  result; struct descriptor_item* name; struct descriptor_item* next; struct descriptor_item* data; struct descriptor_item* items; } ;
struct descriptor {int /*<<< orphan*/  result; struct descriptor* name; struct descriptor* next; struct descriptor* data; struct descriptor* items; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_free (struct descriptor_item*) ; 

__attribute__((used)) static void
descriptor_free(struct descriptor *desc)
{
	struct descriptor_item *desc_item;

	for (desc_item = desc->items; desc_item;)
	{
		struct descriptor_item *di;

		ecpg_free(desc_item->data);
		di = desc_item;
		desc_item = desc_item->next;
		ecpg_free(di);
	}

	ecpg_free(desc->name);
	PQclear(desc->result);
	ecpg_free(desc);
}