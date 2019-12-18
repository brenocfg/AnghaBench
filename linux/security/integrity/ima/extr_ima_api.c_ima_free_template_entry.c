#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ima_template_entry {TYPE_2__* template_data; TYPE_1__* template_desc; } ;
struct TYPE_4__ {struct ima_template_entry* data; } ;
struct TYPE_3__ {int num_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ima_template_entry*) ; 

void ima_free_template_entry(struct ima_template_entry *entry)
{
	int i;

	for (i = 0; i < entry->template_desc->num_fields; i++)
		kfree(entry->template_data[i].data);

	kfree(entry);
}