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
struct timezone {int dummy; } ;
struct timeval {int tv_sec; int tv_usec; } ;
struct pollfd {int fd; long revents; int /*<<< orphan*/  events; } ;
struct hpet_info {long hi_flags; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_EPI ; 
 int /*<<< orphan*/  HPET_IE_ON ; 
 int /*<<< orphan*/  HPET_INFO ; 
 int /*<<< orphan*/  HPET_IRQFREQ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  POLLIN ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,struct timezone*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int read (int,long*,int) ; 
 int /*<<< orphan*/  stderr ; 

void
hpet_poll(int argc, const char **argv)
{
	unsigned long		freq;
	int			iterations, i, fd;
	struct pollfd		pfd;
	struct hpet_info	info;
	struct timeval		stv, etv;
	struct timezone		tz;
	long			usec;

	if (argc != 3) {
		fprintf(stderr, "hpet_poll: device-name freq iterations\n");
		return;
	}

	freq = atoi(argv[1]);
	iterations = atoi(argv[2]);

	fd = open(argv[0], O_RDONLY);

	if (fd < 0) {
		fprintf(stderr, "hpet_poll: open of %s failed\n", argv[0]);
		return;
	}

	if (ioctl(fd, HPET_IRQFREQ, freq) < 0) {
		fprintf(stderr, "hpet_poll: HPET_IRQFREQ failed\n");
		goto out;
	}

	if (ioctl(fd, HPET_INFO, &info) < 0) {
		fprintf(stderr, "hpet_poll: failed to get info\n");
		goto out;
	}

	fprintf(stderr, "hpet_poll: info.hi_flags 0x%lx\n", info.hi_flags);

	if (info.hi_flags && (ioctl(fd, HPET_EPI, 0) < 0)) {
		fprintf(stderr, "hpet_poll: HPET_EPI failed\n");
		goto out;
	}

	if (ioctl(fd, HPET_IE_ON, 0) < 0) {
		fprintf(stderr, "hpet_poll, HPET_IE_ON failed\n");
		goto out;
	}

	pfd.fd = fd;
	pfd.events = POLLIN;

	for (i = 0; i < iterations; i++) {
		pfd.revents = 0;
		gettimeofday(&stv, &tz);
		if (poll(&pfd, 1, -1) < 0)
			fprintf(stderr, "hpet_poll: poll failed\n");
		else {
			long 	data;

			gettimeofday(&etv, &tz);
			usec = stv.tv_sec * 1000000 + stv.tv_usec;
			usec = (etv.tv_sec * 1000000 + etv.tv_usec) - usec;

			fprintf(stderr,
				"hpet_poll: expired time = 0x%lx\n", usec);

			fprintf(stderr, "hpet_poll: revents = 0x%x\n",
				pfd.revents);

			if (read(fd, &data, sizeof(data)) != sizeof(data)) {
				fprintf(stderr, "hpet_poll: read failed\n");
			}
			else
				fprintf(stderr, "hpet_poll: data 0x%lx\n",
					data);
		}
	}

out:
	close(fd);
	return;
}