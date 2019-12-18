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
struct stat {int dummy; } ;
struct perf_pmu_alias {int /*<<< orphan*/  scale; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  scale ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int perf_pmu__convert_scale (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int perf_pmu__parse_scale(struct perf_pmu_alias *alias, char *dir, char *name)
{
	struct stat st;
	ssize_t sret;
	char scale[128];
	int fd, ret = -1;
	char path[PATH_MAX];

	scnprintf(path, PATH_MAX, "%s/%s.scale", dir, name);

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -1;

	if (fstat(fd, &st) < 0)
		goto error;

	sret = read(fd, scale, sizeof(scale)-1);
	if (sret < 0)
		goto error;

	if (scale[sret - 1] == '\n')
		scale[sret - 1] = '\0';
	else
		scale[sret] = '\0';

	ret = perf_pmu__convert_scale(scale, NULL, &alias->scale);
error:
	close(fd);
	return ret;
}