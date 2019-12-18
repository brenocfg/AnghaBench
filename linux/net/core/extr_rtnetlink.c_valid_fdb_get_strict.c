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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ndmsg {int ndm_flags; int ndm_ifindex; scalar_t__ ndm_type; scalar_t__ ndm_state; scalar_t__ ndm_pad2; scalar_t__ ndm_pad1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
#define  NDA_LLADDR 131 
#define  NDA_MASTER 130 
 int NDA_MAX ; 
#define  NDA_VLAN 129 
#define  NDA_VNI 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int NTF_MASTER ; 
 int NTF_SELF ; 
 int fdb_vid_parse (struct nlattr*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nda_policy ; 
 int* nla_data (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int valid_fdb_get_strict(const struct nlmsghdr *nlh,
				struct nlattr **tb, u8 *ndm_flags,
				int *br_idx, int *brport_idx, u8 **addr,
				u16 *vid, struct netlink_ext_ack *extack)
{
	struct ndmsg *ndm;
	int err, i;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ndm))) {
		NL_SET_ERR_MSG(extack, "Invalid header for fdb get request");
		return -EINVAL;
	}

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_type) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for fdb get request");
		return -EINVAL;
	}

	if (ndm->ndm_flags & ~(NTF_MASTER | NTF_SELF)) {
		NL_SET_ERR_MSG(extack, "Invalid flags in header for fdb get request");
		return -EINVAL;
	}

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(struct ndmsg), tb,
					    NDA_MAX, nda_policy, extack);
	if (err < 0)
		return err;

	*ndm_flags = ndm->ndm_flags;
	*brport_idx = ndm->ndm_ifindex;
	for (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NDA_MASTER:
			*br_idx = nla_get_u32(tb[i]);
			break;
		case NDA_LLADDR:
			if (nla_len(tb[i]) != ETH_ALEN) {
				NL_SET_ERR_MSG(extack, "Invalid address in fdb get request");
				return -EINVAL;
			}
			*addr = nla_data(tb[i]);
			break;
		case NDA_VLAN:
			err = fdb_vid_parse(tb[i], vid, extack);
			if (err)
				return err;
			break;
		case NDA_VNI:
			break;
		default:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in fdb get request");
			return -EINVAL;
		}
	}

	return 0;
}