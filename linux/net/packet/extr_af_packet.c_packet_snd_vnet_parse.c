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
struct virtio_net_hdr {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int __packet_snd_vnet_parse (struct virtio_net_hdr*,size_t) ; 
 int /*<<< orphan*/  copy_from_iter_full (struct virtio_net_hdr*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int packet_snd_vnet_parse(struct msghdr *msg, size_t *len,
				 struct virtio_net_hdr *vnet_hdr)
{
	if (*len < sizeof(*vnet_hdr))
		return -EINVAL;
	*len -= sizeof(*vnet_hdr);

	if (!copy_from_iter_full(vnet_hdr, sizeof(*vnet_hdr), &msg->msg_iter))
		return -EFAULT;

	return __packet_snd_vnet_parse(vnet_hdr, *len);
}