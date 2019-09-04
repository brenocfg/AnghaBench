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

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 char* get_tracing_file (char*) ; 
 int /*<<< orphan*/  output_fd ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_tracing_file (char*) ; 
 int record_file (char*,int) ; 
 int stat (char*,struct stat*) ; 
 int write (int /*<<< orphan*/ ,unsigned long long*,int) ; 

__attribute__((used)) static int record_saved_cmdline(void)
{
	unsigned long long size;
	char *path;
	struct stat st;
	int ret, err = 0;

	path = get_tracing_file("saved_cmdlines");
	if (!path) {
		pr_debug("can't get tracing/saved_cmdline");
		return -ENOMEM;
	}

	ret = stat(path, &st);
	if (ret < 0) {
		/* not found */
		size = 0;
		if (write(output_fd, &size, 8) != 8)
			err = -EIO;
		goto out;
	}
	err = record_file(path, 8);

out:
	put_tracing_file(path);
	return err;
}