#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  qthreshold; int /*<<< orphan*/  copy_len; int /*<<< orphan*/  group; } ;
struct TYPE_4__ {int /*<<< orphan*/  logflags; int /*<<< orphan*/  level; } ;
struct TYPE_6__ {TYPE_2__ ulog; TYPE_1__ log; } ;
struct nf_loginfo {int type; TYPE_3__ u; } ;
struct nft_log {scalar_t__ prefix; struct nf_loginfo loginfo; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_LOG_FLAGS ; 
 int /*<<< orphan*/  NFTA_LOG_GROUP ; 
 int /*<<< orphan*/  NFTA_LOG_LEVEL ; 
 int /*<<< orphan*/  NFTA_LOG_PREFIX ; 
 int /*<<< orphan*/  NFTA_LOG_QTHRESHOLD ; 
 int /*<<< orphan*/  NFTA_LOG_SNAPLEN ; 
 int NF_LOG_F_COPY_LEN ; 
#define  NF_LOG_TYPE_LOG 129 
#define  NF_LOG_TYPE_ULOG 128 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct nft_log* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_log_null_prefix ; 
 int /*<<< orphan*/  nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nft_log_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_log *priv = nft_expr_priv(expr);
	const struct nf_loginfo *li = &priv->loginfo;

	if (priv->prefix != nft_log_null_prefix)
		if (nla_put_string(skb, NFTA_LOG_PREFIX, priv->prefix))
			goto nla_put_failure;
	switch (li->type) {
	case NF_LOG_TYPE_LOG:
		if (nla_put_be32(skb, NFTA_LOG_LEVEL, htonl(li->u.log.level)))
			goto nla_put_failure;

		if (li->u.log.logflags) {
			if (nla_put_be32(skb, NFTA_LOG_FLAGS,
					 htonl(li->u.log.logflags)))
				goto nla_put_failure;
		}
		break;
	case NF_LOG_TYPE_ULOG:
		if (nla_put_be16(skb, NFTA_LOG_GROUP, htons(li->u.ulog.group)))
			goto nla_put_failure;

		if (li->u.ulog.flags & NF_LOG_F_COPY_LEN) {
			if (nla_put_be32(skb, NFTA_LOG_SNAPLEN,
					 htonl(li->u.ulog.copy_len)))
				goto nla_put_failure;
		}
		if (li->u.ulog.qthreshold) {
			if (nla_put_be16(skb, NFTA_LOG_QTHRESHOLD,
					 htons(li->u.ulog.qthreshold)))
				goto nla_put_failure;
		}
		break;
	}
	return 0;

nla_put_failure:
	return -1;
}