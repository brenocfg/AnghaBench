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
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ndmsg {int ndm_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUD_PERMANENT ; 
 int dev_mc_del (struct net_device*,unsigned char const*) ; 
 int dev_uc_del (struct net_device*,unsigned char const*) ; 
 scalar_t__ is_link_local_ether_addr (unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_unicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int ndo_dflt_fdb_del(struct ndmsg *ndm,
		     struct nlattr *tb[],
		     struct net_device *dev,
		     const unsigned char *addr, u16 vid)
{
	int err = -EINVAL;

	/* If aging addresses are supported device will need to
	 * implement its own handler for this.
	 */
	if (!(ndm->ndm_state & NUD_PERMANENT)) {
		pr_info("%s: FDB only supports static addresses\n", dev->name);
		return err;
	}

	if (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr))
		err = dev_uc_del(dev, addr);
	else if (is_multicast_ether_addr(addr))
		err = dev_mc_del(dev, addr);

	return err;
}