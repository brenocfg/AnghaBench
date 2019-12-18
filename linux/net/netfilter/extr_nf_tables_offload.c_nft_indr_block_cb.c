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
struct nft_chain {int dummy; } ;
struct nft_base_chain {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;
struct net {TYPE_1__ nft; } ;
typedef  int /*<<< orphan*/  flow_indr_block_bind_cb_t ;
typedef  enum flow_block_command { ____Placeholder_flow_block_command } flow_block_command ;

/* Variables and functions */
 struct nft_chain* __nft_offload_get_chain (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nft_base_chain* nft_base_chain (struct nft_chain*) ; 
 int /*<<< orphan*/  nft_indr_block_ing_cmd (struct net_device*,struct nft_base_chain*,int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static void nft_indr_block_cb(struct net_device *dev,
			      flow_indr_block_bind_cb_t *cb, void *cb_priv,
			      enum flow_block_command cmd)
{
	struct net *net = dev_net(dev);
	struct nft_chain *chain;

	mutex_lock(&net->nft.commit_mutex);
	chain = __nft_offload_get_chain(dev);
	if (chain) {
		struct nft_base_chain *basechain;

		basechain = nft_base_chain(chain);
		nft_indr_block_ing_cmd(dev, basechain, cb, cb_priv, cmd);
	}
	mutex_unlock(&net->nft.commit_mutex);
}