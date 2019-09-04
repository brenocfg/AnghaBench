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
struct xt_tgchk_param {int family; struct ipt_ip* entryinfo; struct xt_CHECKSUM_info* targinfo; } ;
struct xt_CHECKSUM_info {int operation; } ;
struct ipt_ip {int invflags; int flags; int /*<<< orphan*/  proto; } ;
struct ip6t_ip6 {int invflags; int flags; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int EINVAL ; 
 int IP6T_F_PROTO ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int XT_CHECKSUM_OP_FILL ; 
 int XT_INV_PROTO ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 

__attribute__((used)) static int checksum_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_CHECKSUM_info *einfo = par->targinfo;
	const struct ip6t_ip6 *i6 = par->entryinfo;
	const struct ipt_ip *i4 = par->entryinfo;

	if (einfo->operation & ~XT_CHECKSUM_OP_FILL) {
		pr_info_ratelimited("unsupported CHECKSUM operation %x\n",
				    einfo->operation);
		return -EINVAL;
	}
	if (!einfo->operation)
		return -EINVAL;

	switch (par->family) {
	case NFPROTO_IPV4:
		if (i4->proto == IPPROTO_UDP &&
		    (i4->invflags & XT_INV_PROTO) == 0)
			return 0;
		break;
	case NFPROTO_IPV6:
		if ((i6->flags & IP6T_F_PROTO) &&
		    i6->proto == IPPROTO_UDP &&
		    (i6->invflags & XT_INV_PROTO) == 0)
			return 0;
		break;
	}

	pr_warn_once("CHECKSUM should be avoided.  If really needed, restrict with \"-p udp\" and only use in OUTPUT\n");
	return 0;
}