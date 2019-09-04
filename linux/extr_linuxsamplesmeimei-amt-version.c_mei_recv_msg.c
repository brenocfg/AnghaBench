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
struct mei {int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mei_deinit (struct mei*) ; 
 int /*<<< orphan*/  mei_err (struct mei*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_msg (struct mei*,char*,scalar_t__) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t mei_recv_msg(struct mei *me, unsigned char *buffer,
			ssize_t len, unsigned long timeout)
{
	ssize_t rc;

	mei_msg(me, "call read length = %zd\n", len);

	rc = read(me->fd, buffer, len);
	if (rc < 0) {
		mei_err(me, "read failed with status %zd %s\n",
				rc, strerror(errno));
		mei_deinit(me);
	} else {
		mei_msg(me, "read succeeded with result %zd\n", rc);
	}
	return rc;
}