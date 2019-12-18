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
typedef  int __u32 ;

/* Variables and functions */

__attribute__((used)) static size_t mask_bitmap4(const __u32 *bitmap, const __u32 *mask,
		__u32 *res, size_t len)
{
	size_t i;
	__u32 tmp;

	while (len > 0 && (bitmap[len-1] == 0 || mask[len-1] == 0))
		len--;
	for (i = len; i-- > 0;) {
		tmp = bitmap[i] & mask[i];
		res[i] = tmp;
	}
	return len;
}