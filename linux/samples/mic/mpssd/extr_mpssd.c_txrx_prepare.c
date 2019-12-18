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
struct virtio_net_hdr {int dummy; } ;
struct mic_vring {int dummy; } ;
struct mic_copy_desc {int vr_idx; int update_used; TYPE_1__* iov; } ;
typedef  void* ssize_t ;
struct TYPE_2__ {void* iov_len; } ;

/* Variables and functions */
 int VIRTIO_ID_NET ; 

__attribute__((used)) static inline void txrx_prepare(int type, bool tx, struct mic_vring *vr,
				struct mic_copy_desc *copy, ssize_t len)
{
	copy->vr_idx = tx ? 0 : 1;
	copy->update_used = true;
	if (type == VIRTIO_ID_NET)
		copy->iov[1].iov_len = len - sizeof(struct virtio_net_hdr);
	else
		copy->iov[0].iov_len = len;
}