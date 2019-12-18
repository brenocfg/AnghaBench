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
struct hpet_info {int hi_ireqfreq; int hi_flags; int hi_hpet; int hi_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_INFO ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct hpet_info*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
hpet_info(int argc, const char **argv)
{
	struct hpet_info	info;
	int			fd;

	if (argc != 1) {
		fprintf(stderr, "hpet_info: device-name\n");
		return;
	}

	fd = open(argv[0], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "hpet_info: open of %s failed\n", argv[0]);
		return;
	}

	if (ioctl(fd, HPET_INFO, &info) < 0) {
		fprintf(stderr, "hpet_info: failed to get info\n");
		goto out;
	}

	fprintf(stderr, "hpet_info: hi_irqfreq 0x%lx hi_flags 0x%lx ",
		info.hi_ireqfreq, info.hi_flags);
	fprintf(stderr, "hi_hpet %d hi_timer %d\n",
		info.hi_hpet, info.hi_timer);

out:
	close(fd);
	return;
}