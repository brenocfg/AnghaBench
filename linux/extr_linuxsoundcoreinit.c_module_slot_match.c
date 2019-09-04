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
struct module {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int module_slot_match(struct module *module, int idx)
{
	int match = 1;
#ifdef MODULE
	const char *s1, *s2;

	if (!module || !*module->name || !slots[idx])
		return 0;

	s1 = module->name;
	s2 = slots[idx];
	if (*s2 == '!') {
		match = 0; /* negative match */
		s2++;
	}
	/* compare module name strings
	 * hyphens are handled as equivalent with underscore
	 */
	for (;;) {
		char c1 = *s1++;
		char c2 = *s2++;
		if (c1 == '-')
			c1 = '_';
		if (c2 == '-')
			c2 = '_';
		if (c1 != c2)
			return !match;
		if (!c1)
			break;
	}
#endif /* MODULE */
	return match;
}