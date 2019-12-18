#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  val; } ;
struct tcp_fastopen_metrics {TYPE_1__ cookie; scalar_t__ last_syn_loss; scalar_t__ syn_loss; scalar_t__ mss; } ;
struct TYPE_5__ {int family; } ;
struct tcp_metrics_block {int* tcpm_vals; struct tcp_fastopen_metrics tcpm_fastopen; scalar_t__ tcpm_stamp; TYPE_2__ tcpm_saddr; TYPE_2__ tcpm_daddr; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_ADDR_IPV4 ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_ADDR_IPV6 ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_AGE ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_FOPEN_COOKIE ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_FOPEN_MSS ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_FOPEN_SYN_DROPS ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_PAD ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_SADDR_IPV4 ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_SADDR_IPV6 ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_VALS ; 
 int TCP_METRIC_MAX_KERNEL ; 
 int TCP_METRIC_RTT ; 
 int TCP_METRIC_RTTVAR ; 
 int TCP_METRIC_RTTVAR_US ; 
 int TCP_METRIC_RTT_US ; 
 int /*<<< orphan*/  fastopen_seqlock ; 
 int /*<<< orphan*/  inetpeer_get_addr_v4 (TYPE_2__*) ; 
 int /*<<< orphan*/  inetpeer_get_addr_v6 (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int max (int,unsigned int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_msecs (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int,int) ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int tcp_metrics_fill_info(struct sk_buff *msg,
				 struct tcp_metrics_block *tm)
{
	struct nlattr *nest;
	int i;

	switch (tm->tcpm_daddr.family) {
	case AF_INET:
		if (nla_put_in_addr(msg, TCP_METRICS_ATTR_ADDR_IPV4,
				    inetpeer_get_addr_v4(&tm->tcpm_daddr)) < 0)
			goto nla_put_failure;
		if (nla_put_in_addr(msg, TCP_METRICS_ATTR_SADDR_IPV4,
				    inetpeer_get_addr_v4(&tm->tcpm_saddr)) < 0)
			goto nla_put_failure;
		break;
	case AF_INET6:
		if (nla_put_in6_addr(msg, TCP_METRICS_ATTR_ADDR_IPV6,
				     inetpeer_get_addr_v6(&tm->tcpm_daddr)) < 0)
			goto nla_put_failure;
		if (nla_put_in6_addr(msg, TCP_METRICS_ATTR_SADDR_IPV6,
				     inetpeer_get_addr_v6(&tm->tcpm_saddr)) < 0)
			goto nla_put_failure;
		break;
	default:
		return -EAFNOSUPPORT;
	}

	if (nla_put_msecs(msg, TCP_METRICS_ATTR_AGE,
			  jiffies - tm->tcpm_stamp,
			  TCP_METRICS_ATTR_PAD) < 0)
		goto nla_put_failure;

	{
		int n = 0;

		nest = nla_nest_start_noflag(msg, TCP_METRICS_ATTR_VALS);
		if (!nest)
			goto nla_put_failure;
		for (i = 0; i < TCP_METRIC_MAX_KERNEL + 1; i++) {
			u32 val = tm->tcpm_vals[i];

			if (!val)
				continue;
			if (i == TCP_METRIC_RTT) {
				if (nla_put_u32(msg, TCP_METRIC_RTT_US + 1,
						val) < 0)
					goto nla_put_failure;
				n++;
				val = max(val / 1000, 1U);
			}
			if (i == TCP_METRIC_RTTVAR) {
				if (nla_put_u32(msg, TCP_METRIC_RTTVAR_US + 1,
						val) < 0)
					goto nla_put_failure;
				n++;
				val = max(val / 1000, 1U);
			}
			if (nla_put_u32(msg, i + 1, val) < 0)
				goto nla_put_failure;
			n++;
		}
		if (n)
			nla_nest_end(msg, nest);
		else
			nla_nest_cancel(msg, nest);
	}

	{
		struct tcp_fastopen_metrics tfom_copy[1], *tfom;
		unsigned int seq;

		do {
			seq = read_seqbegin(&fastopen_seqlock);
			tfom_copy[0] = tm->tcpm_fastopen;
		} while (read_seqretry(&fastopen_seqlock, seq));

		tfom = tfom_copy;
		if (tfom->mss &&
		    nla_put_u16(msg, TCP_METRICS_ATTR_FOPEN_MSS,
				tfom->mss) < 0)
			goto nla_put_failure;
		if (tfom->syn_loss &&
		    (nla_put_u16(msg, TCP_METRICS_ATTR_FOPEN_SYN_DROPS,
				tfom->syn_loss) < 0 ||
		     nla_put_msecs(msg, TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS,
				jiffies - tfom->last_syn_loss,
				TCP_METRICS_ATTR_PAD) < 0))
			goto nla_put_failure;
		if (tfom->cookie.len > 0 &&
		    nla_put(msg, TCP_METRICS_ATTR_FOPEN_COOKIE,
			    tfom->cookie.len, tfom->cookie.val) < 0)
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}