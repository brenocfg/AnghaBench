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
struct ima_template_field {int /*<<< orphan*/  field_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ima_template_field const*) ; 
 int /*<<< orphan*/  IMA_TEMPLATE_FIELD_ID_MAX_LEN ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct ima_template_field const* supported_fields ; 

__attribute__((used)) static const struct ima_template_field *
lookup_template_field(const char *field_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(supported_fields); i++)
		if (strncmp(supported_fields[i].field_id, field_id,
			    IMA_TEMPLATE_FIELD_ID_MAX_LEN) == 0)
			return &supported_fields[i];
	return NULL;
}