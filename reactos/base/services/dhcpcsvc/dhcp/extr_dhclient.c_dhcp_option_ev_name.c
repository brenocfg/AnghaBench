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
struct dhcp_option {char* name; } ;

/* Variables and functions */

int
dhcp_option_ev_name(char *buf, size_t buflen, struct dhcp_option *option)
{
	int i;

	for (i = 0; option->name[i]; i++) {
		if (i + 1 == buflen)
			return 0;
		if (option->name[i] == '-')
			buf[i] = '_';
		else
			buf[i] = option->name[i];
	}

	buf[i] = 0;
	return 1;
}