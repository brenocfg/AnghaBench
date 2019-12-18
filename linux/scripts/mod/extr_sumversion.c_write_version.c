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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int,unsigned long,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*,unsigned long,...) ; 
 scalar_t__ write (int,char const*,scalar_t__) ; 

__attribute__((used)) static void write_version(const char *filename, const char *sum,
			  unsigned long offset)
{
	int fd;

	fd = open(filename, O_RDWR);
	if (fd < 0) {
		warn("changing sum in %s failed: %s\n",
			filename, strerror(errno));
		return;
	}

	if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
		warn("changing sum in %s:%lu failed: %s\n",
			filename, offset, strerror(errno));
		goto out;
	}

	if (write(fd, sum, strlen(sum)+1) != strlen(sum)+1) {
		warn("writing sum in %s failed: %s\n",
			filename, strerror(errno));
		goto out;
	}
out:
	close(fd);
}