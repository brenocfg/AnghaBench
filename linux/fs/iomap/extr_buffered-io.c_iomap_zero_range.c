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
struct iomap_ops {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMAP_ZERO ; 
 scalar_t__ iomap_apply (struct inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct iomap_ops const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomap_zero_range_actor ; 

int
iomap_zero_range(struct inode *inode, loff_t pos, loff_t len, bool *did_zero,
		const struct iomap_ops *ops)
{
	loff_t ret;

	while (len > 0) {
		ret = iomap_apply(inode, pos, len, IOMAP_ZERO,
				ops, did_zero, iomap_zero_range_actor);
		if (ret <= 0)
			return ret;

		pos += ret;
		len -= ret;
	}

	return 0;
}