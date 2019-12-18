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
struct sort_dimension {int /*<<< orphan*/  name; } ;
struct perf_hpp_list {int dummy; } ;
struct hpp_dimension {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct sort_dimension*) ; 
 int ESRCH ; 
 int __hpp_dimension__add_output (struct perf_hpp_list*,struct sort_dimension*) ; 
 int __sort_dimension__add_output (struct perf_hpp_list*,struct sort_dimension*) ; 
 struct sort_dimension* bstack_sort_dimensions ; 
 struct sort_dimension* common_sort_dimensions ; 
 struct sort_dimension* hpp_sort_dimensions ; 
 struct sort_dimension* memory_sort_dimensions ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int output_field_add(struct perf_hpp_list *list, char *tok)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(common_sort_dimensions); i++) {
		struct sort_dimension *sd = &common_sort_dimensions[i];

		if (strncasecmp(tok, sd->name, strlen(tok)))
			continue;

		return __sort_dimension__add_output(list, sd);
	}

	for (i = 0; i < ARRAY_SIZE(hpp_sort_dimensions); i++) {
		struct hpp_dimension *hd = &hpp_sort_dimensions[i];

		if (strncasecmp(tok, hd->name, strlen(tok)))
			continue;

		return __hpp_dimension__add_output(list, hd);
	}

	for (i = 0; i < ARRAY_SIZE(bstack_sort_dimensions); i++) {
		struct sort_dimension *sd = &bstack_sort_dimensions[i];

		if (strncasecmp(tok, sd->name, strlen(tok)))
			continue;

		return __sort_dimension__add_output(list, sd);
	}

	for (i = 0; i < ARRAY_SIZE(memory_sort_dimensions); i++) {
		struct sort_dimension *sd = &memory_sort_dimensions[i];

		if (strncasecmp(tok, sd->name, strlen(tok)))
			continue;

		return __sort_dimension__add_output(list, sd);
	}

	return -ESRCH;
}