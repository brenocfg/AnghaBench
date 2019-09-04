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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int NFT_REG32_00 ; 
 unsigned int NFT_REG32_SIZE ; 
 unsigned int NFT_REG_SIZE ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int nla_put_be32 (struct sk_buff*,unsigned int,int /*<<< orphan*/ ) ; 

int nft_dump_register(struct sk_buff *skb, unsigned int attr, unsigned int reg)
{
	if (reg % (NFT_REG_SIZE / NFT_REG32_SIZE) == 0)
		reg = reg / (NFT_REG_SIZE / NFT_REG32_SIZE);
	else
		reg = reg - NFT_REG_SIZE / NFT_REG32_SIZE + NFT_REG32_00;

	return nla_put_be32(skb, attr, htonl(reg));
}