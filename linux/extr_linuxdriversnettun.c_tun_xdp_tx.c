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
struct xdp_frame {int dummy; } ;
struct xdp_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  XDP_XMIT_FLUSH ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int tun_xdp_xmit (struct net_device*,int,struct xdp_frame**,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tun_xdp_tx(struct net_device *dev, struct xdp_buff *xdp)
{
	struct xdp_frame *frame = convert_to_xdp_frame(xdp);

	if (unlikely(!frame))
		return -EOVERFLOW;

	return tun_xdp_xmit(dev, 1, &frame, XDP_XMIT_FLUSH);
}