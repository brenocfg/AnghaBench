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
struct virtqueue {int dummy; } ;
struct virtnet_info {TYPE_1__* dev; scalar_t__ big_packets; } ;
struct virtio_net_hdr_mrg_rxbuf {int dummy; } ;
struct TYPE_2__ {unsigned int max_mtu; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 unsigned int const ETH_HLEN ; 
 scalar_t__ GOOD_PACKET_LEN ; 
 unsigned int IP_MAX_MTU ; 
 unsigned int const VLAN_HLEN ; 
 unsigned int max (unsigned int const,unsigned int const) ; 
 unsigned int virtqueue_get_vring_size (struct virtqueue*) ; 

__attribute__((used)) static unsigned int mergeable_min_buf_len(struct virtnet_info *vi, struct virtqueue *vq)
{
	const unsigned int hdr_len = sizeof(struct virtio_net_hdr_mrg_rxbuf);
	unsigned int rq_size = virtqueue_get_vring_size(vq);
	unsigned int packet_len = vi->big_packets ? IP_MAX_MTU : vi->dev->max_mtu;
	unsigned int buf_len = hdr_len + ETH_HLEN + VLAN_HLEN + packet_len;
	unsigned int min_buf_len = DIV_ROUND_UP(buf_len, rq_size);

	return max(max(min_buf_len, hdr_len) - hdr_len,
		   (unsigned int)GOOD_PACKET_LEN);
}