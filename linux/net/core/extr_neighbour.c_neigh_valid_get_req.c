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
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct neigh_table {scalar_t__ key_len; } ;
struct ndmsg {int ndm_flags; int ndm_ifindex; int /*<<< orphan*/  ndm_family; scalar_t__ ndm_type; scalar_t__ ndm_state; scalar_t__ ndm_pad2; scalar_t__ ndm_pad1; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
#define  NDA_DST 128 
 int NDA_MAX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int NTF_PROXY ; 
 int /*<<< orphan*/  nda_policy ; 
 struct neigh_table* neigh_find_table (int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int neigh_valid_get_req(const struct nlmsghdr *nlh,
			       struct neigh_table **tbl,
			       void **dst, int *dev_idx, u8 *ndm_flags,
			       struct netlink_ext_ack *extack)
{
	struct nlattr *tb[NDA_MAX + 1];
	struct ndmsg *ndm;
	int err, i;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ndm))) {
		NL_SET_ERR_MSG(extack, "Invalid header for neighbor get request");
		return -EINVAL;
	}

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_type) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for neighbor get request");
		return -EINVAL;
	}

	if (ndm->ndm_flags & ~NTF_PROXY) {
		NL_SET_ERR_MSG(extack, "Invalid flags in header for neighbor get request");
		return -EINVAL;
	}

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(struct ndmsg), tb,
					    NDA_MAX, nda_policy, extack);
	if (err < 0)
		return err;

	*ndm_flags = ndm->ndm_flags;
	*dev_idx = ndm->ndm_ifindex;
	*tbl = neigh_find_table(ndm->ndm_family);
	if (*tbl == NULL) {
		NL_SET_ERR_MSG(extack, "Unsupported family in header for neighbor get request");
		return -EAFNOSUPPORT;
	}

	for (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NDA_DST:
			if (nla_len(tb[i]) != (int)(*tbl)->key_len) {
				NL_SET_ERR_MSG(extack, "Invalid network address in neighbor get request");
				return -EINVAL;
			}
			*dst = nla_data(tb[i]);
			break;
		default:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in neighbor get request");
			return -EINVAL;
		}
	}

	return 0;
}