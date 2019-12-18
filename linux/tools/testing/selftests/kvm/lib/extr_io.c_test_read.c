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
 size_t read (int,char*,size_t) ; 

ssize_t test_read(int fd, void *buf, size_t count)
{
	ssize_t rc;
	ssize_t num_read = 0;
	size_t num_left = count;
	char *ptr = buf;

	/* Note: Count of zero is allowed (see "If count is zero" portion of
	 * read(2) manpage for details.
	 */
	TEST_ASSERT(count >= 0, "Unexpected count, count: %li", count);

	do {
		rc = read(fd, ptr, num_left);

		switch (rc) {
		case -1:
			TEST_ASSERT(errno == EAGAIN || errno == EINTR,
				    "Unexpected read failure,\n"
				    "  rc: %zi errno: %i", rc, errno);
			break;

		case 0:
			TEST_ASSERT(false, "Unexpected EOF,\n"
				    "  rc: %zi num_read: %zi num_left: %zu",
				    rc, num_read, num_left);
			break;

		default:
			TEST_ASSERT(rc > 0, "Unexpected ret from read,\n"
				    "  rc: %zi errno: %i", rc, errno);
			num_read += rc;
			num_left -= rc;
			ptr += rc;
			break;
		}
	} while (num_read < count);

	return num_read;
}