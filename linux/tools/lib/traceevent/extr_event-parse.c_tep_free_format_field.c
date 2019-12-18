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
struct tep_format_field {scalar_t__ alias; scalar_t__ name; struct tep_format_field* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tep_format_field*) ; 

void tep_free_format_field(struct tep_format_field *field)
{
	free(field->type);
	if (field->alias != field->name)
		free(field->alias);
	free(field->name);
	free(field);
}