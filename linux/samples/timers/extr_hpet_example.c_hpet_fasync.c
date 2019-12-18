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
struct hpet_info {int hi_flags; } ;
typedef  int /*<<< orphan*/  sig_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  F_SETOWN ; 
 int /*<<< orphan*/  HPET_EPI ; 
 int /*<<< orphan*/  HPET_IE_ON ; 
 int /*<<< orphan*/  HPET_INFO ; 
 int /*<<< orphan*/  HPET_IRQFREQ ; 
 int O_ASYNC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIG_ERR ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getpid () ; 
 int /*<<< orphan*/  hpet_sigio ; 
 int hpet_sigio_count ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
hpet_fasync(int argc, const char **argv)
{
	unsigned long		freq;
	int			iterations, i, fd, value;
	sig_t			oldsig;
	struct hpet_info	info;

	hpet_sigio_count = 0;
	fd = -1;

	if ((oldsig = signal(SIGIO, hpet_sigio)) == SIG_ERR) {
		fprintf(stderr, "hpet_fasync: failed to set signal handler\n");
		return;
	}

	if (argc != 3) {
		fprintf(stderr, "hpet_fasync: device-name freq iterations\n");
		goto out;
	}

	fd = open(argv[0], O_RDONLY);

	if (fd < 0) {
		fprintf(stderr, "hpet_fasync: failed to open %s\n", argv[0]);
		return;
	}


	if ((fcntl(fd, F_SETOWN, getpid()) == 1) ||
		((value = fcntl(fd, F_GETFL)) == 1) ||
		(fcntl(fd, F_SETFL, value | O_ASYNC) == 1)) {
		fprintf(stderr, "hpet_fasync: fcntl failed\n");
		goto out;
	}

	freq = atoi(argv[1]);
	iterations = atoi(argv[2]);

	if (ioctl(fd, HPET_IRQFREQ, freq) < 0) {
		fprintf(stderr, "hpet_fasync: HPET_IRQFREQ failed\n");
		goto out;
	}

	if (ioctl(fd, HPET_INFO, &info) < 0) {
		fprintf(stderr, "hpet_fasync: failed to get info\n");
		goto out;
	}

	fprintf(stderr, "hpet_fasync: info.hi_flags 0x%lx\n", info.hi_flags);

	if (info.hi_flags && (ioctl(fd, HPET_EPI, 0) < 0)) {
		fprintf(stderr, "hpet_fasync: HPET_EPI failed\n");
		goto out;
	}

	if (ioctl(fd, HPET_IE_ON, 0) < 0) {
		fprintf(stderr, "hpet_fasync, HPET_IE_ON failed\n");
		goto out;
	}

	for (i = 0; i < iterations; i++) {
		(void) pause();
		fprintf(stderr, "hpet_fasync: count = %d\n", hpet_sigio_count);
	}

out:
	signal(SIGIO, oldsig);

	if (fd >= 0)
		close(fd);

	return;
}