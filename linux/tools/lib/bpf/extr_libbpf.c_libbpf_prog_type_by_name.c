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
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;
struct TYPE_3__ {int prog_type; int expected_attach_type; int /*<<< orphan*/  len; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libbpf_get_type_names (int) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 TYPE_1__* section_names ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int libbpf_prog_type_by_name(const char *name, enum bpf_prog_type *prog_type,
			     enum bpf_attach_type *expected_attach_type)
{
	char *type_names;
	int i;

	if (!name)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(section_names); i++) {
		if (strncmp(name, section_names[i].sec, section_names[i].len))
			continue;
		*prog_type = section_names[i].prog_type;
		*expected_attach_type = section_names[i].expected_attach_type;
		return 0;
	}
	pr_warning("failed to guess program type based on ELF section name '%s'\n", name);
	type_names = libbpf_get_type_names(false);
	if (type_names != NULL) {
		pr_info("supported section(type) names are:%s\n", type_names);
		free(type_names);
	}

	return -EINVAL;
}