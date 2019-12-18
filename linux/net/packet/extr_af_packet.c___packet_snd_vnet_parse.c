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
struct virtio_net_hdr {int flags; int /*<<< orphan*/  hdr_len; int /*<<< orphan*/  csum_offset; int /*<<< orphan*/  csum_start; } ;

/* Variables and functions */
 int EINVAL ; 
 int VIRTIO_NET_HDR_F_NEEDS_CSUM ; 
 int /*<<< orphan*/  __cpu_to_virtio16 (int /*<<< orphan*/ ,size_t) ; 
 size_t __virtio16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_le () ; 

__attribute__((used)) static int __packet_snd_vnet_parse(struct virtio_net_hdr *vnet_hdr, size_t len)
{
	if ((vnet_hdr->flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
	    (__virtio16_to_cpu(vio_le(), vnet_hdr->csum_start) +
	     __virtio16_to_cpu(vio_le(), vnet_hdr->csum_offset) + 2 >
	      __virtio16_to_cpu(vio_le(), vnet_hdr->hdr_len)))
		vnet_hdr->hdr_len = __cpu_to_virtio16(vio_le(),
			 __virtio16_to_cpu(vio_le(), vnet_hdr->csum_start) +
			__virtio16_to_cpu(vio_le(), vnet_hdr->csum_offset) + 2);

	if (__virtio16_to_cpu(vio_le(), vnet_hdr->hdr_len) > len)
		return -EINVAL;

	return 0;
}