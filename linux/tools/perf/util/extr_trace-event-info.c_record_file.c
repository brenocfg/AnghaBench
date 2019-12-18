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
typedef  int /*<<< orphan*/  u64 ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int EIO ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ bigendian () ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_fd ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ pwrite (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int write (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int record_file(const char *file, ssize_t hdr_sz)
{
	unsigned long long size = 0;
	char buf[BUFSIZ], *sizep;
	off_t hdr_pos = lseek(output_fd, 0, SEEK_CUR);
	int r, fd;
	int err = -EIO;

	fd = open(file, O_RDONLY);
	if (fd < 0) {
		pr_debug("Can't read '%s'", file);
		return -errno;
	}

	/* put in zeros for file size, then fill true size later */
	if (hdr_sz) {
		if (write(output_fd, &size, hdr_sz) != hdr_sz)
			goto out;
	}

	do {
		r = read(fd, buf, BUFSIZ);
		if (r > 0) {
			size += r;
			if (write(output_fd, buf, r) != r)
				goto out;
		}
	} while (r > 0);

	/* ugh, handle big-endian hdr_size == 4 */
	sizep = (char*)&size;
	if (bigendian())
		sizep += sizeof(u64) - hdr_sz;

	if (hdr_sz && pwrite(output_fd, sizep, hdr_sz, hdr_pos) < 0) {
		pr_debug("writing file size failed\n");
		goto out;
	}

	err = 0;
out:
	close(fd);
	return err;
}