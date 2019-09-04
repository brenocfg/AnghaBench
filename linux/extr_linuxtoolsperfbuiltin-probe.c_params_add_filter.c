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
struct TYPE_2__ {scalar_t__ filter; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 TYPE_1__ params ; 
 int /*<<< orphan*/  pr_debug2 (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ strfilter__new (char const*,char const**) ; 
 int strfilter__or (scalar_t__,char const*,char const**) ; 

__attribute__((used)) static int params_add_filter(const char *str)
{
	const char *err = NULL;
	int ret = 0;

	pr_debug2("Add filter: %s\n", str);
	if (!params.filter) {
		params.filter = strfilter__new(str, &err);
		if (!params.filter)
			ret = err ? -EINVAL : -ENOMEM;
	} else
		ret = strfilter__or(params.filter, str, &err);

	if (ret == -EINVAL) {
		pr_err("Filter parse error at %td.\n", err - str + 1);
		pr_err("Source: \"%s\"\n", str);
		pr_err("         %*c\n", (int)(err - str + 1), '^');
	}

	return ret;
}