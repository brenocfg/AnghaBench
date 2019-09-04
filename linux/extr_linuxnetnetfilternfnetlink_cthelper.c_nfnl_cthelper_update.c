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
struct nf_conntrack_helper {int /*<<< orphan*/  flags; void* queue_num; } ;

/* Variables and functions */
 int EBUSY ; 
 size_t NFCTH_POLICY ; 
 size_t NFCTH_PRIV_DATA_LEN ; 
 size_t NFCTH_QUEUE_NUM ; 
 size_t NFCTH_STATUS ; 
#define  NFCT_HELPER_STATUS_DISABLED 129 
#define  NFCT_HELPER_STATUS_ENABLED 128 
 int /*<<< orphan*/  NF_CT_HELPER_F_CONFIGURED ; 
 int nfnl_cthelper_update_policy (struct nf_conntrack_helper*,struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfnl_cthelper_update(const struct nlattr * const tb[],
		     struct nf_conntrack_helper *helper)
{
	int ret;

	if (tb[NFCTH_PRIV_DATA_LEN])
		return -EBUSY;

	if (tb[NFCTH_POLICY]) {
		ret = nfnl_cthelper_update_policy(helper, tb[NFCTH_POLICY]);
		if (ret < 0)
			return ret;
	}
	if (tb[NFCTH_QUEUE_NUM])
		helper->queue_num = ntohl(nla_get_be32(tb[NFCTH_QUEUE_NUM]));

	if (tb[NFCTH_STATUS]) {
		int status = ntohl(nla_get_be32(tb[NFCTH_STATUS]));

		switch(status) {
		case NFCT_HELPER_STATUS_ENABLED:
			helper->flags |= NF_CT_HELPER_F_CONFIGURED;
			break;
		case NFCT_HELPER_STATUS_DISABLED:
			helper->flags &= ~NF_CT_HELPER_F_CONFIGURED;
			break;
		}
	}
	return 0;
}