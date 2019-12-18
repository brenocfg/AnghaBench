#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct nft_chain {int dummy; } ;
struct TYPE_3__ {struct net_device* dev; } ;
struct nft_base_chain {scalar_t__ policy; TYPE_1__ ops; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
typedef  enum flow_block_command { ____Placeholder_flow_block_command } flow_block_command ;
struct TYPE_4__ {scalar_t__ ndo_setup_tc; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FLOW_BLOCK_BIND ; 
 scalar_t__ NF_DROP ; 
 struct nft_base_chain* nft_base_chain (struct nft_chain*) ; 
 int nft_block_offload_cmd (struct nft_base_chain*,struct net_device*,int) ; 
 int nft_indr_block_offload_cmd (struct nft_base_chain*,struct net_device*,int) ; 
 int /*<<< orphan*/  nft_is_base_chain (struct nft_chain*) ; 

__attribute__((used)) static int nft_flow_offload_chain(struct nft_chain *chain,
				  u8 *ppolicy,
				  enum flow_block_command cmd)
{
	struct nft_base_chain *basechain;
	struct net_device *dev;
	u8 policy;

	if (!nft_is_base_chain(chain))
		return -EOPNOTSUPP;

	basechain = nft_base_chain(chain);
	dev = basechain->ops.dev;
	if (!dev)
		return -EOPNOTSUPP;

	policy = ppolicy ? *ppolicy : basechain->policy;

	/* Only default policy to accept is supported for now. */
	if (cmd == FLOW_BLOCK_BIND && policy == NF_DROP)
		return -EOPNOTSUPP;

	if (dev->netdev_ops->ndo_setup_tc)
		return nft_block_offload_cmd(basechain, dev, cmd);
	else
		return nft_indr_block_offload_cmd(basechain, dev, cmd);
}