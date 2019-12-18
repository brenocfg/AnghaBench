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
struct utsname {char const* nodename; char const* release; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 scalar_t__ mkdir (char const*,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ uname (struct utsname*) ; 

FILE *prepare_output(const char *dirname)
{
	FILE *output = NULL;
	int len;
	char *filename, *filename_tmp;
	struct utsname sysdata;
	DIR *dir;

	dir = opendir(dirname);
	if (dir == NULL) {
		if (mkdir(dirname, 0755)) {
			perror("mkdir");
			fprintf(stderr, "error: Cannot create dir %s\n",
				dirname);
			return NULL;
		}
	}

	len = strlen(dirname) + 30;
	filename = malloc(sizeof(char) * len);
	if (!filename) {
		perror("malloc");
		goto out_dir;
	}

	if (uname(&sysdata) == 0) {
		len += strlen(sysdata.nodename) + strlen(sysdata.release);
		filename_tmp = realloc(filename, sizeof(*filename) * len);

		if (filename_tmp == NULL) {
			free(filename);
			perror("realloc");
			goto out_dir;
		}

		filename = filename_tmp;
		snprintf(filename, len - 1, "%s/benchmark_%s_%s_%li.log",
			dirname, sysdata.nodename, sysdata.release, time(NULL));
	} else {
		snprintf(filename, len - 1, "%s/benchmark_%li.log",
			dirname, time(NULL));
	}

	dprintf("logfilename: %s\n", filename);

	output = fopen(filename, "w+");
	if (output == NULL) {
		perror("fopen");
		fprintf(stderr, "error: unable to open logfile\n");
		goto out;
	}

	fprintf(stdout, "Logfile: %s\n", filename);

	fprintf(output, "#round load sleep performance powersave percentage\n");
out:
	free(filename);
out_dir:
	closedir(dir);
	return output;
}