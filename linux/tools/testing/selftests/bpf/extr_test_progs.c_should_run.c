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
struct test_selector {int num_set_len; scalar_t__* num_set; scalar_t__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strstr (char const*,scalar_t__*) ; 

__attribute__((used)) static bool should_run(struct test_selector *sel, int num, const char *name)
{
	if (sel->name && sel->name[0] && !strstr(name, sel->name))
		return false;

	if (!sel->num_set)
		return true;

	return num < sel->num_set_len && sel->num_set[num];
}