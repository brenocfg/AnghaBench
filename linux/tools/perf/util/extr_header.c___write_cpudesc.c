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
struct feat_fd {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int do_write_string (struct feat_fd*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 char* skip_spaces (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __write_cpudesc(struct feat_fd *ff, const char *cpuinfo_proc)
{
	FILE *file;
	char *buf = NULL;
	char *s, *p;
	const char *search = cpuinfo_proc;
	size_t len = 0;
	int ret = -1;

	if (!search)
		return -1;

	file = fopen("/proc/cpuinfo", "r");
	if (!file)
		return -1;

	while (getline(&buf, &len, file) > 0) {
		ret = strncmp(buf, search, strlen(search));
		if (!ret)
			break;
	}

	if (ret) {
		ret = -1;
		goto done;
	}

	s = buf;

	p = strchr(buf, ':');
	if (p && *(p+1) == ' ' && *(p+2))
		s = p + 2;
	p = strchr(s, '\n');
	if (p)
		*p = '\0';

	/* squash extra space characters (branding string) */
	p = s;
	while (*p) {
		if (isspace(*p)) {
			char *r = p + 1;
			char *q = skip_spaces(r);
			*p = ' ';
			if (q != (p+1))
				while ((*r++ = *q++));
		}
		p++;
	}
	ret = do_write_string(ff, s);
done:
	free(buf);
	fclose(file);
	return ret;
}