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
struct TYPE_2__ {int type; } ;
struct nft_offload_ctx {TYPE_1__ dep; } ;
typedef  enum nft_offload_dep_type { ____Placeholder_nft_offload_dep_type } nft_offload_dep_type ;

/* Variables and functions */

void nft_offload_set_dependency(struct nft_offload_ctx *ctx,
				enum nft_offload_dep_type type)
{
	ctx->dep.type = type;
}