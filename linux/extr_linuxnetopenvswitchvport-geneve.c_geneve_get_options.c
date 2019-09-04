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
struct vport {int dummy; } ;
struct sk_buff {int dummy; } ;
struct geneve_port {int /*<<< orphan*/  dst_port; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_TUNNEL_ATTR_DST_PORT ; 
 struct geneve_port* geneve_vport (struct vport const*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int geneve_get_options(const struct vport *vport,
			      struct sk_buff *skb)
{
	struct geneve_port *geneve_port = geneve_vport(vport);

	if (nla_put_u16(skb, OVS_TUNNEL_ATTR_DST_PORT, geneve_port->dst_port))
		return -EMSGSIZE;
	return 0;
}