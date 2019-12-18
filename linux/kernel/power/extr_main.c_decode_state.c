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
typedef  size_t suspend_state_t ;

/* Variables and functions */
 size_t PM_SUSPEND_MAX ; 
 size_t PM_SUSPEND_MIN ; 
 size_t PM_SUSPEND_ON ; 
 char* memchr (char const*,char,size_t) ; 
 char** pm_states ; 
 scalar_t__ str_has_prefix (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static suspend_state_t decode_state(const char *buf, size_t n)
{
#ifdef CONFIG_SUSPEND
	suspend_state_t state;
#endif
	char *p;
	int len;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	/* Check hibernation first. */
	if (len == 4 && str_has_prefix(buf, "disk"))
		return PM_SUSPEND_MAX;

#ifdef CONFIG_SUSPEND
	for (state = PM_SUSPEND_MIN; state < PM_SUSPEND_MAX; state++) {
		const char *label = pm_states[state];

		if (label && len == strlen(label) && !strncmp(buf, label, len))
			return state;
	}
#endif

	return PM_SUSPEND_ON;
}