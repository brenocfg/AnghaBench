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
struct script_desc {void* args; void* half_liner; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* ltrim (char*) ; 
 void* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int read_script_info(struct script_desc *desc, const char *filename)
{
	char line[BUFSIZ], *p;
	FILE *fp;

	fp = fopen(filename, "r");
	if (!fp)
		return -1;

	while (fgets(line, sizeof(line), fp)) {
		p = ltrim(line);
		if (strlen(p) == 0)
			continue;
		if (*p != '#')
			continue;
		p++;
		if (strlen(p) && *p == '!')
			continue;

		p = ltrim(p);
		if (strlen(p) && p[strlen(p) - 1] == '\n')
			p[strlen(p) - 1] = '\0';

		if (!strncmp(p, "description:", strlen("description:"))) {
			p += strlen("description:");
			desc->half_liner = strdup(ltrim(p));
			continue;
		}

		if (!strncmp(p, "args:", strlen("args:"))) {
			p += strlen("args:");
			desc->args = strdup(ltrim(p));
			continue;
		}
	}

	fclose(fp);

	return 0;
}