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
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  pr_notice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_template_modsig(const struct ima_template_desc *template)
{
#define MSG "template with 'modsig' field also needs 'd-modsig' field\n"
	bool has_modsig, has_dmodsig;
	static bool checked;
	int i;

	/* We only need to notify the user once. */
	if (checked)
		return;

	has_modsig = has_dmodsig = false;
	for (i = 0; i < template->num_fields; i++) {
		if (!strcmp(template->fields[i]->field_id, "modsig"))
			has_modsig = true;
		else if (!strcmp(template->fields[i]->field_id, "d-modsig"))
			has_dmodsig = true;
	}

	if (has_modsig && !has_dmodsig)
		pr_notice(MSG);

	checked = true;
#undef MSG
}