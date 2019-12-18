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
struct hist_field {int flags; struct hist_field** operands; } ;

/* Variables and functions */
 int HIST_FIELD_FL_VAR_REF ; 
 unsigned int HIST_FIELD_OPERANDS_MAX ; 
 int /*<<< orphan*/  __destroy_hist_field (struct hist_field*) ; 

__attribute__((used)) static void destroy_hist_field(struct hist_field *hist_field,
			       unsigned int level)
{
	unsigned int i;

	if (level > 3)
		return;

	if (!hist_field)
		return;

	if (hist_field->flags & HIST_FIELD_FL_VAR_REF)
		return; /* var refs will be destroyed separately */

	for (i = 0; i < HIST_FIELD_OPERANDS_MAX; i++)
		destroy_hist_field(hist_field->operands[i], level + 1);

	__destroy_hist_field(hist_field);
}