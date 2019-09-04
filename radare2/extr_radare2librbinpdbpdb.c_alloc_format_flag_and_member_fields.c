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
typedef  int /*<<< orphan*/  RListIter ;
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ *) ; 

int alloc_format_flag_and_member_fields(RList *ptmp, char **flags_format_field, int *members_amount, char ***members_name_field) {
	int i = 0, size = 0;

	RListIter *it2 = r_list_iterator (ptmp);
	while (r_list_iter_next (it2)) {
		(void) r_list_iter_get (it2);
		*members_amount = *members_amount + 1;
	}
	if (!*members_amount) {
		return 0;
	}
	*flags_format_field = (char *) malloc (*members_amount + 1);
	memset (*flags_format_field, 0, *members_amount + 1);

	size = sizeof *members_name_field * (*members_amount);
	*members_name_field = (char **) malloc (size);
	for (i = 0; i < *members_amount; i++) {
		(*members_name_field)[i] = 0;
	}
	return 1;
}