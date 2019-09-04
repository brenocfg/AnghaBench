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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFLA_MACSEC_CIPHER_SUITE ; 
 size_t IFLA_MACSEC_ICV_LEN ; 
 size_t IFLA_MACSEC_PORT ; 
 size_t IFLA_MACSEC_SCI ; 
 int macsec_changelink_common (struct net_device*,struct nlattr**) ; 

__attribute__((used)) static int macsec_changelink(struct net_device *dev, struct nlattr *tb[],
			     struct nlattr *data[],
			     struct netlink_ext_ack *extack)
{
	if (!data)
		return 0;

	if (data[IFLA_MACSEC_CIPHER_SUITE] ||
	    data[IFLA_MACSEC_ICV_LEN] ||
	    data[IFLA_MACSEC_SCI] ||
	    data[IFLA_MACSEC_PORT])
		return -EINVAL;

	return macsec_changelink_common(dev, data);
}