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
typedef  int /*<<< orphan*/  v ;
struct perf_event_read {unsigned long l1d_misses; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 unsigned long CACHELINE_SIZE ; 
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ memalign (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  perf_event_disable (int) ; 
 int perf_event_enable (int) ; 
 int perf_event_open_counter (int /*<<< orphan*/ ,int,int) ; 
 int perf_event_reset (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,char,int,int,int) ; 
 int read (int,struct perf_event_read*,int) ; 
 scalar_t__ read_debugfs_file (char*,int*) ; 
 int /*<<< orphan*/  set_dscr (int) ; 
 int /*<<< orphan*/  syscall_loop (char*,unsigned long,unsigned long) ; 
 scalar_t__ write_debugfs_file (char*,int) ; 

int rfi_flush_test(void)
{
	char *p;
	int repetitions = 10;
	int fd, passes = 0, iter, rc = 0;
	struct perf_event_read v;
	__u64 l1d_misses_total = 0;
	unsigned long iterations = 100000, zero_size = 24 * 1024;
	unsigned long l1d_misses_expected;
	int rfi_flush_org, rfi_flush;

	SKIP_IF(geteuid() != 0);

	if (read_debugfs_file("powerpc/rfi_flush", &rfi_flush_org)) {
		perror("Unable to read powerpc/rfi_flush debugfs file");
		SKIP_IF(1);
	}

	rfi_flush = rfi_flush_org;

	fd = perf_event_open_counter(PERF_TYPE_RAW, /* L1d miss */ 0x400f0, -1);
	FAIL_IF(fd < 0);

	p = (char *)memalign(zero_size, CACHELINE_SIZE);

	FAIL_IF(perf_event_enable(fd));

	set_dscr(1);

	iter = repetitions;

	/*
	 * We expect to see l1d miss for each cacheline access when rfi_flush
	 * is set. Allow a small variation on this.
	 */
	l1d_misses_expected = iterations * (zero_size / CACHELINE_SIZE - 2);

again:
	FAIL_IF(perf_event_reset(fd));

	syscall_loop(p, iterations, zero_size);

	FAIL_IF(read(fd, &v, sizeof(v)) != sizeof(v));

	if (rfi_flush && v.l1d_misses >= l1d_misses_expected)
		passes++;
	else if (!rfi_flush && v.l1d_misses < (l1d_misses_expected / 2))
		passes++;

	l1d_misses_total += v.l1d_misses;

	while (--iter)
		goto again;

	if (passes < repetitions) {
		printf("FAIL (L1D misses with rfi_flush=%d: %llu %c %lu) [%d/%d failures]\n",
		       rfi_flush, l1d_misses_total, rfi_flush ? '<' : '>',
		       rfi_flush ? repetitions * l1d_misses_expected :
		       repetitions * l1d_misses_expected / 2,
		       repetitions - passes, repetitions);
		rc = 1;
	} else
		printf("PASS (L1D misses with rfi_flush=%d: %llu %c %lu) [%d/%d pass]\n",
		       rfi_flush, l1d_misses_total, rfi_flush ? '>' : '<',
		       rfi_flush ? repetitions * l1d_misses_expected :
		       repetitions * l1d_misses_expected / 2,
		       passes, repetitions);

	if (rfi_flush == rfi_flush_org) {
		rfi_flush = !rfi_flush_org;
		if (write_debugfs_file("powerpc/rfi_flush", rfi_flush) < 0) {
			perror("error writing to powerpc/rfi_flush debugfs file");
			return 1;
		}
		iter = repetitions;
		l1d_misses_total = 0;
		passes = 0;
		goto again;
	}

	perf_event_disable(fd);
	close(fd);

	set_dscr(0);

	if (write_debugfs_file("powerpc/rfi_flush", rfi_flush_org) < 0) {
		perror("unable to restore original value of powerpc/rfi_flush debugfs file");
		return 1;
	}

	return rc;
}