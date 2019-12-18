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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
hpet_open_close(int argc, const char **argv)
{
	int	fd;

	if (argc != 1) {
		fprintf(stderr, "hpet_open_close: device-name\n");
		return;
	}

	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		fprintf(stderr, "hpet_open_close: open failed\n");
	else
		close(fd);

	return;
}