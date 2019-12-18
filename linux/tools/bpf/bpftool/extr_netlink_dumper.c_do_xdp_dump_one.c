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

/* Variables and functions */
 size_t IFLA_XDP_ATTACHED ; 
 int /*<<< orphan*/  IFLA_XDP_DRV_PROG_ID ; 
 int /*<<< orphan*/  IFLA_XDP_HW_PROG_ID ; 
 int /*<<< orphan*/  IFLA_XDP_MAX ; 
 int /*<<< orphan*/  IFLA_XDP_PROG_ID ; 
 int /*<<< orphan*/  IFLA_XDP_SKB_PROG_ID ; 
 int /*<<< orphan*/  NET_DUMP_STR (char*,char*,char const*) ; 
 int /*<<< orphan*/  NET_DUMP_UINT (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  NET_END_OBJECT_FINAL ; 
 int /*<<< orphan*/  NET_START_OBJECT ; 
 unsigned char XDP_ATTACHED_DRV ; 
 unsigned char XDP_ATTACHED_HW ; 
 unsigned char XDP_ATTACHED_MULTI ; 
 unsigned char XDP_ATTACHED_NONE ; 
 unsigned char XDP_ATTACHED_SKB ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 unsigned char libbpf_nla_getattr_u8 (struct nlattr*) ; 
 scalar_t__ libbpf_nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_dump_prog_id (struct nlattr**,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int do_xdp_dump_one(struct nlattr *attr, unsigned int ifindex,
			   const char *name)
{
	struct nlattr *tb[IFLA_XDP_MAX + 1];
	unsigned char mode;

	if (libbpf_nla_parse_nested(tb, IFLA_XDP_MAX, attr, NULL) < 0)
		return -1;

	if (!tb[IFLA_XDP_ATTACHED])
		return 0;

	mode = libbpf_nla_getattr_u8(tb[IFLA_XDP_ATTACHED]);
	if (mode == XDP_ATTACHED_NONE)
		return 0;

	NET_START_OBJECT;
	if (name)
		NET_DUMP_STR("devname", "%s", name);
	NET_DUMP_UINT("ifindex", "(%d)", ifindex);

	if (mode == XDP_ATTACHED_MULTI) {
		if (json_output) {
			jsonw_name(json_wtr, "multi_attachments");
			jsonw_start_array(json_wtr);
		}
		xdp_dump_prog_id(tb, IFLA_XDP_SKB_PROG_ID, "generic", true);
		xdp_dump_prog_id(tb, IFLA_XDP_DRV_PROG_ID, "driver", true);
		xdp_dump_prog_id(tb, IFLA_XDP_HW_PROG_ID, "offload", true);
		if (json_output)
			jsonw_end_array(json_wtr);
	} else if (mode == XDP_ATTACHED_DRV) {
		xdp_dump_prog_id(tb, IFLA_XDP_PROG_ID, "driver", false);
	} else if (mode == XDP_ATTACHED_SKB) {
		xdp_dump_prog_id(tb, IFLA_XDP_PROG_ID, "generic", false);
	} else if (mode == XDP_ATTACHED_HW) {
		xdp_dump_prog_id(tb, IFLA_XDP_PROG_ID, "offload", false);
	}

	NET_END_OBJECT_FINAL;
	return 0;
}