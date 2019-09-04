#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct hist_field* name; } ;
struct hist_field {struct hist_field* type; struct hist_field* name; TYPE_1__ var; struct hist_field** operands; } ;

/* Variables and functions */
 unsigned int HIST_FIELD_OPERANDS_MAX ; 
 int /*<<< orphan*/  kfree (struct hist_field*) ; 

__attribute__((used)) static void destroy_hist_field(struct hist_field *hist_field,
			       unsigned int level)
{
	unsigned int i;

	if (level > 3)
		return;

	if (!hist_field)
		return;

	for (i = 0; i < HIST_FIELD_OPERANDS_MAX; i++)
		destroy_hist_field(hist_field->operands[i], level + 1);

	kfree(hist_field->var.name);
	kfree(hist_field->name);
	kfree(hist_field->type);

	kfree(hist_field);
}