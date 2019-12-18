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
typedef  scalar_t__ u32 ;
struct smc_link_group {int /*<<< orphan*/  rtokens_used_mask; TYPE_1__** rtokens; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ rkey; scalar_t__ dma_addr; } ;

/* Variables and functions */
 int ENOENT ; 
 int SMC_RMBS_PER_LGR_MAX ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int smc_rtoken_delete(struct smc_link_group *lgr, __be32 nw_rkey)
{
	u32 rkey = ntohl(nw_rkey);
	int i;

	for (i = 0; i < SMC_RMBS_PER_LGR_MAX; i++) {
		if (lgr->rtokens[i][SMC_SINGLE_LINK].rkey == rkey &&
		    test_bit(i, lgr->rtokens_used_mask)) {
			lgr->rtokens[i][SMC_SINGLE_LINK].rkey = 0;
			lgr->rtokens[i][SMC_SINGLE_LINK].dma_addr = 0;

			clear_bit(i, lgr->rtokens_used_mask);
			return 0;
		}
	}
	return -ENOENT;
}