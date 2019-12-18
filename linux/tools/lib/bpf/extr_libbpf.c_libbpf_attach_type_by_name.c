#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;
struct TYPE_3__ {int attach_type; int /*<<< orphan*/  is_attachable; int /*<<< orphan*/  len; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libbpf_get_type_names (int) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 TYPE_1__* section_names ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int libbpf_attach_type_by_name(const char *name,
			       enum bpf_attach_type *attach_type)
{
	char *type_names;
	int i;

	if (!name)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(section_names); i++) {
		if (strncmp(name, section_names[i].sec, section_names[i].len))
			continue;
		if (!section_names[i].is_attachable)
			return -EINVAL;
		*attach_type = section_names[i].attach_type;
		return 0;
	}
	pr_warning("failed to guess attach type based on ELF section name '%s'\n", name);
	type_names = libbpf_get_type_names(true);
	if (type_names != NULL) {
		pr_info("attachable section(type) names are:%s\n", type_names);
		free(type_names);
	}

	return -EINVAL;
}