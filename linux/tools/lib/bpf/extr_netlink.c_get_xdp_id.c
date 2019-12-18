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
struct xdp_id_md {scalar_t__ ifindex; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; } ;
struct nlattr {int dummy; } ;
struct ifinfomsg {scalar_t__ ifi_index; } ;

/* Variables and functions */
 size_t IFLA_XDP ; 
 size_t IFLA_XDP_ATTACHED ; 
 int /*<<< orphan*/  IFLA_XDP_MAX ; 
 unsigned char XDP_ATTACHED_NONE ; 
 unsigned char get_xdp_id_attr (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libbpf_nla_getattr_u32 (struct nlattr*) ; 
 unsigned char libbpf_nla_getattr_u8 (struct nlattr*) ; 
 int libbpf_nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_xdp_id(void *cookie, void *msg, struct nlattr **tb)
{
	struct nlattr *xdp_tb[IFLA_XDP_MAX + 1];
	struct xdp_id_md *xdp_id = cookie;
	struct ifinfomsg *ifinfo = msg;
	unsigned char mode, xdp_attr;
	int ret;

	if (xdp_id->ifindex && xdp_id->ifindex != ifinfo->ifi_index)
		return 0;

	if (!tb[IFLA_XDP])
		return 0;

	ret = libbpf_nla_parse_nested(xdp_tb, IFLA_XDP_MAX, tb[IFLA_XDP], NULL);
	if (ret)
		return ret;

	if (!xdp_tb[IFLA_XDP_ATTACHED])
		return 0;

	mode = libbpf_nla_getattr_u8(xdp_tb[IFLA_XDP_ATTACHED]);
	if (mode == XDP_ATTACHED_NONE)
		return 0;

	xdp_attr = get_xdp_id_attr(mode, xdp_id->flags);
	if (!xdp_attr || !xdp_tb[xdp_attr])
		return 0;

	xdp_id->id = libbpf_nla_getattr_u32(xdp_tb[xdp_attr]);

	return 0;
}