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
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int dsa_port_fdb_del (struct dsa_port*,unsigned char const*,int /*<<< orphan*/ ) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 

int dsa_legacy_fdb_del(struct ndmsg *ndm, struct nlattr *tb[],
		       struct net_device *dev,
		       const unsigned char *addr, u16 vid)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);

	return dsa_port_fdb_del(dp, addr, vid);
}