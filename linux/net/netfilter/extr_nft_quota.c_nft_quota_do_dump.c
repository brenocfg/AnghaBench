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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nft_quota {int /*<<< orphan*/  flags; int /*<<< orphan*/  consumed; int /*<<< orphan*/  quota; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_QUOTA_BYTES ; 
 int /*<<< orphan*/  NFTA_QUOTA_CONSUMED ; 
 int /*<<< orphan*/  NFTA_QUOTA_FLAGS ; 
 int /*<<< orphan*/  NFTA_QUOTA_PAD ; 
 int /*<<< orphan*/  NFT_QUOTA_DEPLETED_BIT ; 
 int /*<<< orphan*/  NFT_QUOTA_F_DEPLETED ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_quota_do_dump(struct sk_buff *skb, struct nft_quota *priv,
			     bool reset)
{
	u64 consumed, consumed_cap, quota;
	u32 flags = priv->flags;

	/* Since we inconditionally increment consumed quota for each packet
	 * that we see, don't go over the quota boundary in what we send to
	 * userspace.
	 */
	consumed = atomic64_read(&priv->consumed);
	quota = atomic64_read(&priv->quota);
	if (consumed >= quota) {
		consumed_cap = quota;
		flags |= NFT_QUOTA_F_DEPLETED;
	} else {
		consumed_cap = consumed;
	}

	if (nla_put_be64(skb, NFTA_QUOTA_BYTES, cpu_to_be64(quota),
			 NFTA_QUOTA_PAD) ||
	    nla_put_be64(skb, NFTA_QUOTA_CONSUMED, cpu_to_be64(consumed_cap),
			 NFTA_QUOTA_PAD) ||
	    nla_put_be32(skb, NFTA_QUOTA_FLAGS, htonl(flags)))
		goto nla_put_failure;

	if (reset) {
		atomic64_sub(consumed, &priv->consumed);
		clear_bit(NFT_QUOTA_DEPLETED_BIT, &priv->flags);
	}
	return 0;

nla_put_failure:
	return -1;
}