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
typedef  scalar_t__ u64 ;
struct feat_fd {int dummy; } ;
typedef  int /*<<< orphan*/  size ;

/* Variables and functions */
 scalar_t__ BITS_TO_U64 (scalar_t__) ; 
 int do_write (struct feat_fd*,scalar_t__*,int) ; 

__attribute__((used)) static int do_write_bitmap(struct feat_fd *ff, unsigned long *set, u64 size)
{
	u64 *p = (u64 *) set;
	int i, ret;

	ret = do_write(ff, &size, sizeof(size));
	if (ret < 0)
		return ret;

	for (i = 0; (u64) i < BITS_TO_U64(size); i++) {
		ret = do_write(ff, p + i, sizeof(*p));
		if (ret < 0)
			return ret;
	}

	return 0;
}