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
 int /*<<< orphan*/  isspace (char) ; 
 char* skip_spaces (char*) ; 
 char* strdup (char*) ; 
 char* strim (char*) ; 

__attribute__((used)) static int disasm_line__parse(char *line, const char **namep, char **rawp)
{
	char tmp, *name = skip_spaces(line);

	if (name[0] == '\0')
		return -1;

	*rawp = name + 1;

	while ((*rawp)[0] != '\0' && !isspace((*rawp)[0]))
		++*rawp;

	tmp = (*rawp)[0];
	(*rawp)[0] = '\0';
	*namep = strdup(name);

	if (*namep == NULL)
		goto out;

	(*rawp)[0] = tmp;
	*rawp = strim(*rawp);

	return 0;

out:
	return -1;
}