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
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 char* ltrim (char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int disasm_line__parse(char *line, const char **namep, char **rawp)
{
	char tmp, *name = ltrim(line);

	if (name[0] == '\0')
		return -1;

	*rawp = name + 1;

	while ((*rawp)[0] != '\0' && !isspace((*rawp)[0]))
		++*rawp;

	tmp = (*rawp)[0];
	(*rawp)[0] = '\0';
	*namep = strdup(name);

	if (*namep == NULL)
		goto out_free_name;

	(*rawp)[0] = tmp;
	*rawp = ltrim(*rawp);

	return 0;

out_free_name:
	free((void *)namep);
	*namep = NULL;
	return -1;
}