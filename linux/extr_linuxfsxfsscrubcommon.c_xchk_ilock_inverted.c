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
typedef  int /*<<< orphan*/  uint ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int EDEADLOCK ; 
 int /*<<< orphan*/  delay (int) ; 
 scalar_t__ xfs_ilock_nowait (struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xchk_ilock_inverted(
	struct xfs_inode	*ip,
	uint			lock_mode)
{
	int			i;

	for (i = 0; i < 20; i++) {
		if (xfs_ilock_nowait(ip, lock_mode))
			return 0;
		delay(1);
	}
	return -EDEADLOCK;
}