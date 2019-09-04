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
struct net_device {int dummy; } ;
struct TYPE_3__ {int version; scalar_t__ protocol; int ihl; } ;
struct ip_tunnel_parm {int i_flags; int o_flags; scalar_t__ o_key; scalar_t__ i_key; TYPE_1__ iph; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifru_data; } ;
struct ifreq {TYPE_2__ ifr_ifru; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int GRE_KEY ; 
 scalar_t__ IPPROTO_IPIP ; 
 int SIOCADDTUNNEL ; 
 int SIOCCHGTUNNEL ; 
 int SIOCDELTUNNEL ; 
 int VTI_ISVTI ; 
 scalar_t__ copy_from_user (struct ip_tunnel_parm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct ip_tunnel_parm*,int) ; 
 int ip_tunnel_ioctl (struct net_device*,struct ip_tunnel_parm*,int) ; 

__attribute__((used)) static int
vti_tunnel_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int err = 0;
	struct ip_tunnel_parm p;

	if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
		return -EFAULT;

	if (cmd == SIOCADDTUNNEL || cmd == SIOCCHGTUNNEL) {
		if (p.iph.version != 4 || p.iph.protocol != IPPROTO_IPIP ||
		    p.iph.ihl != 5)
			return -EINVAL;
	}

	if (!(p.i_flags & GRE_KEY))
		p.i_key = 0;
	if (!(p.o_flags & GRE_KEY))
		p.o_key = 0;

	p.i_flags = VTI_ISVTI;

	err = ip_tunnel_ioctl(dev, &p, cmd);
	if (err)
		return err;

	if (cmd != SIOCDELTUNNEL) {
		p.i_flags |= GRE_KEY;
		p.o_flags |= GRE_KEY;
	}

	if (copy_to_user(ifr->ifr_ifru.ifru_data, &p, sizeof(p)))
		return -EFAULT;
	return 0;
}