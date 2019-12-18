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
struct nft_payload {int dummy; } ;
struct TYPE_2__ {int protonum; } ;
struct nft_offload_ctx {TYPE_1__ dep; } ;
struct nft_flow_rule {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int nft_payload_offload_tcp (struct nft_offload_ctx*,struct nft_flow_rule*,struct nft_payload const*) ; 
 int nft_payload_offload_udp (struct nft_offload_ctx*,struct nft_flow_rule*,struct nft_payload const*) ; 

__attribute__((used)) static int nft_payload_offload_th(struct nft_offload_ctx *ctx,
				  struct nft_flow_rule *flow,
				  const struct nft_payload *priv)
{
	int err;

	switch (ctx->dep.protonum) {
	case IPPROTO_TCP:
		err = nft_payload_offload_tcp(ctx, flow, priv);
		break;
	case IPPROTO_UDP:
		err = nft_payload_offload_udp(ctx, flow, priv);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return err;
}