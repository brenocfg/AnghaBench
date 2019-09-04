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
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static inline char *
make_auth_domain_name(char *name)
{
	static char	*prefix = "gss/";
	char		*new;

	new = kmalloc(strlen(name) + strlen(prefix) + 1, GFP_KERNEL);
	if (new) {
		strcpy(new, prefix);
		strcat(new, name);
	}
	return new;
}