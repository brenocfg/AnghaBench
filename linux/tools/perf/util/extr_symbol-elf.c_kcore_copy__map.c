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
struct kcore_copy_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ kcore_copy_info__addnew (struct kcore_copy_info*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int kcore_copy__map(struct kcore_copy_info *kci, u64 start, u64 end,
			   u64 pgoff, u64 s, u64 e)
{
	u64 len, offset;

	if (s < start || s >= end)
		return 0;

	offset = (s - start) + pgoff;
	len = e < end ? e - s : end - s;

	return kcore_copy_info__addnew(kci, s, len, offset) ? 0 : -1;
}