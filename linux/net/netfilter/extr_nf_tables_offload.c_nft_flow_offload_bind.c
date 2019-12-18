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
struct TYPE_2__ {int /*<<< orphan*/  cb_list; } ;
struct nft_base_chain {TYPE_1__ flow_block; } ;
struct flow_block_offload {int /*<<< orphan*/  cb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nft_flow_offload_bind(struct flow_block_offload *bo,
				 struct nft_base_chain *basechain)
{
	list_splice(&bo->cb_list, &basechain->flow_block.cb_list);
	return 0;
}