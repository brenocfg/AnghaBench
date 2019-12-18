#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int tun_flags; } ;
struct ip_tunnel_info {TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_FLAGS ; 
 int /*<<< orphan*/  NFT_TUNNEL_F_DONT_FRAGMENT ; 
 int /*<<< orphan*/  NFT_TUNNEL_F_SEQ_NUMBER ; 
 int /*<<< orphan*/  NFT_TUNNEL_F_ZERO_CSUM_TX ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_DONT_FRAGMENT ; 
 int TUNNEL_SEQ ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_flags_dump(struct sk_buff *skb,
				 struct ip_tunnel_info *info)
{
	u32 flags = 0;

	if (info->key.tun_flags & TUNNEL_DONT_FRAGMENT)
		flags |= NFT_TUNNEL_F_DONT_FRAGMENT;
	if (!(info->key.tun_flags & TUNNEL_CSUM))
		flags |= NFT_TUNNEL_F_ZERO_CSUM_TX;
	if (info->key.tun_flags & TUNNEL_SEQ)
		flags |= NFT_TUNNEL_F_SEQ_NUMBER;

	if (nla_put_be32(skb, NFTA_TUNNEL_KEY_FLAGS, htonl(flags)) < 0)
		return -1;

	return 0;
}