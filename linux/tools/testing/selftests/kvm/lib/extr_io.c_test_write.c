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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,size_t,...) ; 
 int /*<<< orphan*/  errno ; 
 size_t write (int,char const*,size_t) ; 

ssize_t test_write(int fd, const void *buf, size_t count)
{
	ssize_t rc;
	ssize_t num_written = 0;
	size_t num_left = count;
	const char *ptr = buf;

	/* Note: Count of zero is allowed (see "RETURN VALUE" portion of
	 * write(2) manpage for details.
	 */
	TEST_ASSERT(count >= 0, "Unexpected count, count: %li", count);

	do {
		rc = write(fd, ptr, num_left);

		switch (rc) {
		case -1:
			TEST_ASSERT(errno == EAGAIN || errno == EINTR,
				    "Unexpected write failure,\n"
				    "  rc: %zi errno: %i", rc, errno);
			continue;

		case 0:
			TEST_ASSERT(false, "Unexpected EOF,\n"
				    "  rc: %zi num_written: %zi num_left: %zu",
				    rc, num_written, num_left);
			break;

		default:
			TEST_ASSERT(rc >= 0, "Unexpected ret from write,\n"
				"  rc: %zi errno: %i", rc, errno);
			num_written += rc;
			num_left -= rc;
			ptr += rc;
			break;
		}
	} while (num_written < count);

	return num_written;
}