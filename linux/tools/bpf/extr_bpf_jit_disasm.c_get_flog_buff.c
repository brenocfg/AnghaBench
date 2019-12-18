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
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static char *get_flog_buff(const char *file, unsigned int *klen)
{
	int fd, ret, len;
	struct stat fi;
	char *buff;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return NULL;

	ret = fstat(fd, &fi);
	if (ret < 0 || !S_ISREG(fi.st_mode))
		goto out;

	len = fi.st_size + 1;
	buff = malloc(len);
	if (!buff)
		goto out;

	memset(buff, 0, len);
	ret = read(fd, buff, len - 1);
	if (ret <= 0)
		goto out_free;

	close(fd);
	*klen = ret;
	return buff;
out_free:
	free(buff);
out:
	close(fd);
	return NULL;
}