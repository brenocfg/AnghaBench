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

/* Variables and functions */
 int /*<<< orphan*/  kfree (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void gssp_hostbased_service(char **principal)
{
	char *c;

	if (!*principal)
		return;

	/* terminate and remove realm part */
	c = strchr(*principal, '@');
	if (c) {
		*c = '\0';

		/* change service-hostname delimiter */
		c = strchr(*principal, '/');
		if (c)
			*c = '@';
	}
	if (!c) {
		/* not a service principal */
		kfree(*principal);
		*principal = NULL;
	}
}