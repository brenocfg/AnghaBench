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
 int /*<<< orphan*/  exit (int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int open_or_die(const char *filename, int flags)
{
	int fd = open(filename, flags);

	if (fd < 0) {
		printf("Failed to open '%s'; "
			"check prerequisites are available\n", filename);
		exit(1);
	}
	return fd;
}