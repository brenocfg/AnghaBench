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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int O_APPEND ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_tracing_file (char const*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,...) ; 
 int /*<<< orphan*/  put_tracing_file (char*) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 size_t write (int,char*,size_t) ; 

__attribute__((used)) static int __write_tracing_file(const char *name, const char *val, bool append)
{
	char *file;
	int fd, ret = -1;
	ssize_t size = strlen(val);
	int flags = O_WRONLY;
	char errbuf[512];
	char *val_copy;

	file = get_tracing_file(name);
	if (!file) {
		pr_debug("cannot get tracing file: %s\n", name);
		return -1;
	}

	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;

	fd = open(file, flags);
	if (fd < 0) {
		pr_debug("cannot open tracing file: %s: %s\n",
			 name, str_error_r(errno, errbuf, sizeof(errbuf)));
		goto out;
	}

	/*
	 * Copy the original value and append a '\n'. Without this,
	 * the kernel can hide possible errors.
	 */
	val_copy = strdup(val);
	if (!val_copy)
		goto out_close;
	val_copy[size] = '\n';

	if (write(fd, val_copy, size + 1) == size + 1)
		ret = 0;
	else
		pr_debug("write '%s' to tracing/%s failed: %s\n",
			 val, name, str_error_r(errno, errbuf, sizeof(errbuf)));

	free(val_copy);
out_close:
	close(fd);
out:
	put_tracing_file(file);
	return ret;
}