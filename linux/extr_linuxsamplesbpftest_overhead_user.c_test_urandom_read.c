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
typedef  int /*<<< orphan*/  buf ;
typedef  int __u64 ;

/* Variables and functions */
 int MAX_CNT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read (int,char*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int time_get_ns () ; 

__attribute__((used)) static void test_urandom_read(int cpu)
{
	__u64 start_time;
	char buf[4];
	int i, fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
		printf("couldn't open /dev/urandom\n");
		exit(1);
	}
	start_time = time_get_ns();
	for (i = 0; i < MAX_CNT; i++) {
		if (read(fd, buf, sizeof(buf)) < 0) {
			printf("failed to read from /dev/urandom: %s\n", strerror(errno));
			close(fd);
			return;
		}
	}
	printf("urandom_read:%d: %lld events per sec\n",
	       cpu, MAX_CNT * 1000000000ll / (time_get_ns() - start_time));
	close(fd);
}