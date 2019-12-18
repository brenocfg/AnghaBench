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
struct file {char* name; struct file* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* conf_get_autoconfig_name () ; 
 int /*<<< orphan*/  env_write_dep (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 struct file* file_list ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ make_parent_dir (char const*) ; 
 int /*<<< orphan*/  rename (char*,char const*) ; 

__attribute__((used)) static int conf_write_dep(const char *name)
{
	struct file *file;
	FILE *out;

	out = fopen("..config.tmp", "w");
	if (!out)
		return 1;
	fprintf(out, "deps_config := \\\n");
	for (file = file_list; file; file = file->next) {
		if (file->next)
			fprintf(out, "\t%s \\\n", file->name);
		else
			fprintf(out, "\t%s\n", file->name);
	}
	fprintf(out, "\n%s: \\\n"
		     "\t$(deps_config)\n\n", conf_get_autoconfig_name());

	env_write_dep(out, conf_get_autoconfig_name());

	fprintf(out, "\n$(deps_config): ;\n");
	fclose(out);

	if (make_parent_dir(name))
		return 1;
	rename("..config.tmp", name);
	return 0;
}