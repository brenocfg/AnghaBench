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
struct TYPE_2__ {scalar_t__ priority; } ;
struct nft_base_chain {TYPE_1__ ops; } ;

/* Variables and functions */
 scalar_t__ USHRT_MAX ; 

int nft_chain_offload_priority(struct nft_base_chain *basechain)
{
	if (basechain->ops.priority <= 0 ||
	    basechain->ops.priority > USHRT_MAX)
		return -1;

	return 0;
}