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
struct mq_attr {int dummy; } ;

/* Variables and functions */
 int DEFFILEMODE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ mq_close (int) ; 
 scalar_t__ mq_getattr (int,struct mq_attr*) ; 
 int mq_open (int /*<<< orphan*/ ,int,int,struct mq_attr*) ; 
 scalar_t__ mq_unlink (int /*<<< orphan*/ ) ; 
 int queue ; 
 int /*<<< orphan*/  queue_path ; 
 int /*<<< orphan*/  shutdown (int,char*,int) ; 

__attribute__((used)) static inline int test_queue_fail(struct mq_attr *attr, struct mq_attr *result)
{
	int flags = O_RDWR | O_EXCL | O_CREAT;
	int perms = DEFFILEMODE;

	if ((queue = mq_open(queue_path, flags, perms, attr)) == -1)
		return 0;
	if (mq_getattr(queue, result))
		shutdown(1, "mq_getattr()", __LINE__);
	if (mq_close(queue))
		shutdown(1, "mq_close()", __LINE__);
	queue = -1;
	if (mq_unlink(queue_path))
		shutdown(1, "mq_unlink()", __LINE__);
	return 1;
}