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
struct msg_group_t {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct msg_group_t* all_groups ; 
 int num_groups ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct msg_group_t *spk_find_msg_group(const char *group_name)
{
	struct msg_group_t *group = NULL;
	int i;

	for (i = 0; i < num_groups; i++) {
		if (!strcmp(all_groups[i].name, group_name)) {
			group = &all_groups[i];
			break;
		}
	}
	return group;
}