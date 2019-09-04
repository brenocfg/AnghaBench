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
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int print_man_page(const char *subpage)
{
	int len;
	char *page;

	len = 10; /* enough for "cpupower-" */
	if (subpage != NULL)
		len += strlen(subpage);

	page = malloc(len);
	if (!page)
		return -ENOMEM;

	sprintf(page, "cpupower");
	if ((subpage != NULL) && strcmp(subpage, "help")) {
		strcat(page, "-");
		strcat(page, subpage);
	}

	execlp("man", "man", page, NULL);

	/* should not be reached */
	return -EINVAL;
}