#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct TYPE_2__ {unsigned int num; struct vring_used* used; struct vring_avail* avail; struct vring_desc* desc; } ;
struct vringh {unsigned long long little_endian; unsigned long long event_indices; int weak_barriers; TYPE_1__ vring; scalar_t__ last_used_idx; scalar_t__ last_avail_idx; scalar_t__ completed; } ;
struct vring_used {int dummy; } ;
struct vring_desc {int dummy; } ;
struct vring_avail {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long VIRTIO_F_VERSION_1 ; 
 int VIRTIO_RING_F_EVENT_IDX ; 
 int /*<<< orphan*/  vringh_bad (char*,unsigned int) ; 

int vringh_init_kern(struct vringh *vrh, u64 features,
		     unsigned int num, bool weak_barriers,
		     struct vring_desc *desc,
		     struct vring_avail *avail,
		     struct vring_used *used)
{
	/* Sane power of 2 please! */
	if (!num || num > 0xffff || (num & (num - 1))) {
		vringh_bad("Bad ring size %u", num);
		return -EINVAL;
	}

	vrh->little_endian = (features & (1ULL << VIRTIO_F_VERSION_1));
	vrh->event_indices = (features & (1 << VIRTIO_RING_F_EVENT_IDX));
	vrh->weak_barriers = weak_barriers;
	vrh->completed = 0;
	vrh->last_avail_idx = 0;
	vrh->last_used_idx = 0;
	vrh->vring.num = num;
	vrh->vring.desc = desc;
	vrh->vring.avail = avail;
	vrh->vring.used = used;
	return 0;
}