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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read (int,char*,int) ; 

__attribute__((used)) static int test_kernel_bit_width(void)
{
	char in[512], *ptr;
	int num = 0, fd;
	ssize_t ret;

	fd = open("/proc/kallsyms", O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	ret = read(fd, in, sizeof(in));
	if (ret <= 0) {
		perror("read");
		exit(1);
	}

	close(fd);

	ptr = in;
	while(!isspace(*ptr)) {
		num++;
		ptr++;
	}

	return num * 4;
}