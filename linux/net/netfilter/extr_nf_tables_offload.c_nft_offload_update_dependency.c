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
typedef  int u32 ;
struct TYPE_2__ {int type; int /*<<< orphan*/  protonum; int /*<<< orphan*/  l3num; } ;
struct nft_offload_ctx {TYPE_1__ dep; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
#define  NFT_OFFLOAD_DEP_NETWORK 129 
#define  NFT_OFFLOAD_DEP_TRANSPORT 128 
 int NFT_OFFLOAD_DEP_UNSPEC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

void nft_offload_update_dependency(struct nft_offload_ctx *ctx,
				   const void *data, u32 len)
{
	switch (ctx->dep.type) {
	case NFT_OFFLOAD_DEP_NETWORK:
		WARN_ON(len != sizeof(__u16));
		memcpy(&ctx->dep.l3num, data, sizeof(__u16));
		break;
	case NFT_OFFLOAD_DEP_TRANSPORT:
		WARN_ON(len != sizeof(__u8));
		memcpy(&ctx->dep.protonum, data, sizeof(__u8));
		break;
	default:
		break;
	}
	ctx->dep.type = NFT_OFFLOAD_DEP_UNSPEC;
}