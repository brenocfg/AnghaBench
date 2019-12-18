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
struct ima_template_desc {int num_fields; TYPE_1__** fields; } ;
struct TYPE_2__ {int /*<<< orphan*/  field_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

bool ima_template_has_modsig(const struct ima_template_desc *ima_template)
{
	int i;

	for (i = 0; i < ima_template->num_fields; i++)
		if (!strcmp(ima_template->fields[i]->field_id, "modsig") ||
		    !strcmp(ima_template->fields[i]->field_id, "d-modsig"))
			return true;

	return false;
}