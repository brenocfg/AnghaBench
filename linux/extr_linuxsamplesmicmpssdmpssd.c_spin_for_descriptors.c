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
struct TYPE_4__ {TYPE_1__* avail; } ;
struct mic_vring {TYPE_2__ vr; } ;
struct mic_info {int dummy; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_3__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ read_avail_idx (struct mic_vring*) ; 
 int /*<<< orphan*/  sched_yield () ; 

__attribute__((used)) static void
spin_for_descriptors(struct mic_info *mic, struct mic_vring *vr)
{
	__u16 avail_idx = read_avail_idx(vr);

	while (avail_idx == le16toh(READ_ONCE(vr->vr.avail->idx))) {
#ifdef DEBUG
		mpsslog("%s %s waiting for desc avail %d info_avail %d\n",
			mic->name, __func__,
			le16toh(vr->vr.avail->idx), vr->info->avail_idx);
#endif
		sched_yield();
	}
}