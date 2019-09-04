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
typedef  int u64 ;
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_mask; } ;
struct perf_event_attr {int exclude_kernel; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PERF_COUNT_HW_INSTRUCTIONS ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mmap_read_self (void*) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  perf_event_open_cloexec_flag () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  segfault_handler ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __test__rdpmc(void)
{
	volatile int tmp = 0;
	u64 i, loops = 1000;
	int n;
	int fd;
	void *addr;
	struct perf_event_attr attr = {
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_INSTRUCTIONS,
		.exclude_kernel = 1,
	};
	u64 delta_sum = 0;
        struct sigaction sa;
	char sbuf[STRERR_BUFSIZE];

	sigfillset(&sa.sa_mask);
	sa.sa_sigaction = segfault_handler;
	sa.sa_flags = 0;
	sigaction(SIGSEGV, &sa, NULL);

	fd = sys_perf_event_open(&attr, 0, -1, -1,
				 perf_event_open_cloexec_flag());
	if (fd < 0) {
		pr_err("Error: sys_perf_event_open() syscall returned "
		       "with %d (%s)\n", fd,
		       str_error_r(errno, sbuf, sizeof(sbuf)));
		return -1;
	}

	addr = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == (void *)(-1)) {
		pr_err("Error: mmap() syscall returned with (%s)\n",
		       str_error_r(errno, sbuf, sizeof(sbuf)));
		goto out_close;
	}

	for (n = 0; n < 6; n++) {
		u64 stamp, now, delta;

		stamp = mmap_read_self(addr);

		for (i = 0; i < loops; i++)
			tmp++;

		now = mmap_read_self(addr);
		loops *= 10;

		delta = now - stamp;
		pr_debug("%14d: %14Lu\n", n, (long long)delta);

		delta_sum += delta;
	}

	munmap(addr, page_size);
	pr_debug("   ");
out_close:
	close(fd);

	if (!delta_sum)
		return -1;

	return 0;
}