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
struct nft_base_chain {int dummy; } ;
struct flow_block_offload {int dummy; } ;
typedef  enum flow_block_command { ____Placeholder_flow_block_command } flow_block_command ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_BLOCK_BIND 129 
#define  FLOW_BLOCK_UNBIND 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int nft_flow_offload_bind (struct flow_block_offload*,struct nft_base_chain*) ; 
 int nft_flow_offload_unbind (struct flow_block_offload*,struct nft_base_chain*) ; 

__attribute__((used)) static int nft_block_setup(struct nft_base_chain *basechain,
			   struct flow_block_offload *bo,
			   enum flow_block_command cmd)
{
	int err;

	switch (cmd) {
	case FLOW_BLOCK_BIND:
		err = nft_flow_offload_bind(bo, basechain);
		break;
	case FLOW_BLOCK_UNBIND:
		err = nft_flow_offload_unbind(bo, basechain);
		break;
	default:
		WARN_ON_ONCE(1);
		err = -EOPNOTSUPP;
	}

	return err;
}