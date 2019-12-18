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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nft_quota {int /*<<< orphan*/  quota; int /*<<< orphan*/  consumed; } ;

/* Variables and functions */
 scalar_t__ atomic64_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool nft_overquota(struct nft_quota *priv,
				 const struct sk_buff *skb)
{
	return atomic64_add_return(skb->len, &priv->consumed) >=
	       atomic64_read(&priv->quota);
}