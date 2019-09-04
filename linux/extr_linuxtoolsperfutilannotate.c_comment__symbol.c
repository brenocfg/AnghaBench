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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int) ; 

__attribute__((used)) static int comment__symbol(char *raw, char *comment, u64 *addrp, char **namep)
{
	char *endptr, *name, *t;

	if (strstr(raw, "(%rip)") == NULL)
		return 0;

	*addrp = strtoull(comment, &endptr, 16);
	if (endptr == comment)
		return 0;
	name = strchr(endptr, '<');
	if (name == NULL)
		return -1;

	name++;

	t = strchr(name, '>');
	if (t == NULL)
		return 0;

	*t = '\0';
	*namep = strdup(name);
	*t = '>';

	return 0;
}