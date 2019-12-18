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
struct obs_x264 {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const* const) ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*) ; 

__attribute__((used)) static const char *validate(struct obs_x264 *obsx264, const char *val,
			    const char *name, const char *const *list)
{
	if (!val || !*val)
		return val;

	while (*list) {
		if (strcmp(val, *list) == 0)
			return val;

		list++;
	}

	warn("Invalid %s: %s", name, val);
	return NULL;
}