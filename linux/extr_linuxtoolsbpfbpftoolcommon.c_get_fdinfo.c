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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int getpid () ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 char* strchr (char*,char) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strstr (char*,char const*) ; 

char *get_fdinfo(int fd, const char *key)
{
	char path[PATH_MAX];
	char *line = NULL;
	size_t line_n = 0;
	ssize_t n;
	FILE *fdi;

	snprintf(path, sizeof(path), "/proc/%d/fdinfo/%d", getpid(), fd);

	fdi = fopen(path, "r");
	if (!fdi) {
		p_err("can't open fdinfo: %s", strerror(errno));
		return NULL;
	}

	while ((n = getline(&line, &line_n, fdi)) > 0) {
		char *value;
		int len;

		if (!strstr(line, key))
			continue;

		fclose(fdi);

		value = strchr(line, '\t');
		if (!value || !value[1]) {
			p_err("malformed fdinfo!?");
			free(line);
			return NULL;
		}
		value++;

		len = strlen(value);
		memmove(line, value, len);
		line[len - 1] = '\0';

		return line;
	}

	p_err("key '%s' not found in fdinfo", key);
	free(line);
	fclose(fdi);
	return NULL;
}