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
typedef  enum net_attach_type { ____Placeholder_net_attach_type } net_attach_type ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int NET_ATTACH_TYPE_XDP_DRIVER ; 
 int NET_ATTACH_TYPE_XDP_GENERIC ; 
 int NET_ATTACH_TYPE_XDP_OFFLOAD ; 
 int /*<<< orphan*/  XDP_FLAGS_DRV_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_HW_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_SKB_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 int bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_attach_detach_xdp(int progfd, enum net_attach_type attach_type,
				int ifindex, bool overwrite)
{
	__u32 flags = 0;

	if (!overwrite)
		flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
	if (attach_type == NET_ATTACH_TYPE_XDP_GENERIC)
		flags |= XDP_FLAGS_SKB_MODE;
	if (attach_type == NET_ATTACH_TYPE_XDP_DRIVER)
		flags |= XDP_FLAGS_DRV_MODE;
	if (attach_type == NET_ATTACH_TYPE_XDP_OFFLOAD)
		flags |= XDP_FLAGS_HW_MODE;

	return bpf_set_link_xdp_fd(ifindex, progfd, flags);
}