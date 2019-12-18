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
typedef  int /*<<< orphan*/  u32 ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ndmsg {int ndm_ifindex; scalar_t__ ndm_type; scalar_t__ ndm_flags; scalar_t__ ndm_state; scalar_t__ ndm_pad2; scalar_t__ ndm_pad1; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NDA_IFINDEX 129 
#define  NDA_MASTER 128 
 int NDA_MAX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 

__attribute__((used)) static int valid_fdb_dump_strict(const struct nlmsghdr *nlh,
				 int *br_idx, int *brport_idx,
				 struct netlink_ext_ack *extack)
{
	struct nlattr *tb[NDA_MAX + 1];
	struct ndmsg *ndm;
	int err, i;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ndm))) {
		NL_SET_ERR_MSG(extack, "Invalid header for fdb dump request");
		return -EINVAL;
	}

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_flags || ndm->ndm_type) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for fdb dump request");
		return -EINVAL;
	}

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(struct ndmsg), tb,
					    NDA_MAX, NULL, extack);
	if (err < 0)
		return err;

	*brport_idx = ndm->ndm_ifindex;
	for (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NDA_IFINDEX:
			if (nla_len(tb[i]) != sizeof(u32)) {
				NL_SET_ERR_MSG(extack, "Invalid IFINDEX attribute in fdb dump request");
				return -EINVAL;
			}
			*brport_idx = nla_get_u32(tb[NDA_IFINDEX]);
			break;
		case NDA_MASTER:
			if (nla_len(tb[i]) != sizeof(u32)) {
				NL_SET_ERR_MSG(extack, "Invalid MASTER attribute in fdb dump request");
				return -EINVAL;
			}
			*br_idx = nla_get_u32(tb[NDA_MASTER]);
			break;
		default:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in fdb dump request");
			return -EINVAL;
		}
	}

	return 0;
}