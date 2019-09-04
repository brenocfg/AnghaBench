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

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long) ; 
 int read (int,char*,int) ; 
 unsigned long strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int check_cpu_dscr_default(char *file, unsigned long val)
{
	char buf[10];
	int fd, rc;

	fd = open(file, O_RDWR);
	if (fd == -1) {
		perror("open() failed");
		return 1;
	}

	rc = read(fd, buf, sizeof(buf));
	if (rc == -1) {
		perror("read() failed");
		return 1;
	}
	close(fd);

	buf[rc] = '\0';
	if (strtol(buf, NULL, 16) != val) {
		printf("DSCR match failed: %ld (system) %ld (cpu)\n",
					val, strtol(buf, NULL, 16));
		return 1;
	}
	return 0;
}