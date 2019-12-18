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
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char fgetc (int /*<<< orphan*/ *) ; 
 char* fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  path__join (char*,int,char const*,char const*) ; 
 char const* strim (char*) ; 

__attribute__((used)) static const char *shell_test__description(char *description, size_t size,
					   const char *path, const char *name)
{
	FILE *fp;
	char filename[PATH_MAX];

	path__join(filename, sizeof(filename), path, name);
	fp = fopen(filename, "r");
	if (!fp)
		return NULL;

	/* Skip shebang */
	while (fgetc(fp) != '\n');

	description = fgets(description, size, fp);
	fclose(fp);

	return description ? strim(description + 1) : NULL;
}