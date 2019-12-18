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

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int read (int,void*,int) ; 
 scalar_t__ repipe ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int __do_read(int fd, void *buf, int size)
{
	int rsize = size;

	while (size) {
		int ret = read(fd, buf, size);

		if (ret <= 0)
			return -1;

		if (repipe) {
			int retw = write(STDOUT_FILENO, buf, ret);

			if (retw <= 0 || retw != ret) {
				pr_debug("repiping input file");
				return -1;
			}
		}

		size -= ret;
		buf += ret;
	}

	return rsize;
}