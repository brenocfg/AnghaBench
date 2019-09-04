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
struct dirent {char const* d_name; } ;
struct cmdnames {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  add_cmdname (struct cmdnames*,char const*,int) ; 
 int /*<<< orphan*/  astrcat (char**,char const*) ; 
 int /*<<< orphan*/  astrcatf (char**,char*,char const*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ has_extension (char const*,char*) ; 
 int /*<<< orphan*/  is_executable (char*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strstarts (char const*,char const*) ; 

__attribute__((used)) static void list_commands_in_dir(struct cmdnames *cmds,
					 const char *path,
					 const char *prefix)
{
	int prefix_len;
	DIR *dir = opendir(path);
	struct dirent *de;
	char *buf = NULL;

	if (!dir)
		return;
	if (!prefix)
		prefix = "perf-";
	prefix_len = strlen(prefix);

	astrcatf(&buf, "%s/", path);

	while ((de = readdir(dir)) != NULL) {
		int entlen;

		if (!strstarts(de->d_name, prefix))
			continue;

		astrcat(&buf, de->d_name);
		if (!is_executable(buf))
			continue;

		entlen = strlen(de->d_name) - prefix_len;
		if (has_extension(de->d_name, ".exe"))
			entlen -= 4;

		add_cmdname(cmds, de->d_name + prefix_len, entlen);
	}
	closedir(dir);
	free(buf);
}