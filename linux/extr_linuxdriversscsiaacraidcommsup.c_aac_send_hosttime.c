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
struct timespec64 {int /*<<< orphan*/  tv_sec; } ;
struct fib {int dummy; } ;
struct aac_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FsaNormal ; 
 int /*<<< orphan*/  SendHostTime ; 
 struct fib* aac_fib_alloc (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fib_data (struct fib*) ; 

int aac_send_hosttime(struct aac_dev *dev, struct timespec64 *now)
{
	int ret = -ENOMEM;
	struct fib *fibptr;
	__le32 *info;

	fibptr = aac_fib_alloc(dev);
	if (!fibptr)
		goto out;

	aac_fib_init(fibptr);
	info = (__le32 *)fib_data(fibptr);
	*info = cpu_to_le32(now->tv_sec); /* overflow in y2106 */
	ret = aac_fib_send(SendHostTime, fibptr, sizeof(*info), FsaNormal,
					1, 1, NULL, NULL);

	/*
	 * Do not set XferState to zero unless
	 * receives a response from F/W
	 */
	if (ret >= 0)
		aac_fib_complete(fibptr);

	/*
	 * FIB should be freed only after
	 * getting the response from the F/W
	 */
	if (ret != -ERESTARTSYS)
		aac_fib_free(fibptr);

out:
	return ret;
}