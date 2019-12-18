#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct scrub_parity {scalar_t__ stripe_len; scalar_t__ nsectors; scalar_t__ logic_start; TYPE_2__* sctx; } ;
struct TYPE_4__ {TYPE_1__* fs_info; } ;
struct TYPE_3__ {int sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,scalar_t__,scalar_t__) ; 
 scalar_t__ div64_u64_rem (scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ div_u64 (scalar_t__,int) ; 

__attribute__((used)) static inline void __scrub_mark_bitmap(struct scrub_parity *sparity,
				       unsigned long *bitmap,
				       u64 start, u64 len)
{
	u64 offset;
	u64 nsectors64;
	u32 nsectors;
	int sectorsize = sparity->sctx->fs_info->sectorsize;

	if (len >= sparity->stripe_len) {
		bitmap_set(bitmap, 0, sparity->nsectors);
		return;
	}

	start -= sparity->logic_start;
	start = div64_u64_rem(start, sparity->stripe_len, &offset);
	offset = div_u64(offset, sectorsize);
	nsectors64 = div_u64(len, sectorsize);

	ASSERT(nsectors64 < UINT_MAX);
	nsectors = (u32)nsectors64;

	if (offset + nsectors <= sparity->nsectors) {
		bitmap_set(bitmap, offset, nsectors);
		return;
	}

	bitmap_set(bitmap, offset, sparity->nsectors - offset);
	bitmap_set(bitmap, 0, nsectors - (sparity->nsectors - offset));
}