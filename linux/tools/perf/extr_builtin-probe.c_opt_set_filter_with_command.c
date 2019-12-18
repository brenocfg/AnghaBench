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
struct option {int /*<<< orphan*/  short_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 TYPE_1__ params ; 
 int params_add_filter (char const*) ; 

__attribute__((used)) static int opt_set_filter_with_command(const struct option *opt,
				       const char *str, int unset)
{
	if (!unset)
		params.command = opt->short_name;

	if (str)
		return params_add_filter(str);

	return 0;
}