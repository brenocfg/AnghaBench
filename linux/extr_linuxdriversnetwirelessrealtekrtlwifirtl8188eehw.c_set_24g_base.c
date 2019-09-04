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
typedef  size_t u32 ;
struct txpower_info_2g {int** index_cck_base; int** index_bw40_base; int** bw20_diff; int** ofdm_diff; int** bw40_diff; int** cck_diff; } ;

/* Variables and functions */
 int MAX_CHNL_GROUP_24G ; 
 int MAX_TX_COUNT ; 

__attribute__((used)) static void set_24g_base(struct txpower_info_2g *pwrinfo24g, u32 rfpath)
{
	int group, txcnt;

	for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
		pwrinfo24g->index_cck_base[rfpath][group] = 0x2D;
		pwrinfo24g->index_bw40_base[rfpath][group] = 0x2D;
	}
	for (txcnt = 0; txcnt < MAX_TX_COUNT; txcnt++) {
		if (txcnt == 0) {
			pwrinfo24g->bw20_diff[rfpath][0] = 0x02;
			pwrinfo24g->ofdm_diff[rfpath][0] = 0x04;
		} else {
			pwrinfo24g->bw20_diff[rfpath][txcnt] = 0xFE;
			pwrinfo24g->bw40_diff[rfpath][txcnt] = 0xFE;
			pwrinfo24g->cck_diff[rfpath][txcnt] =	0xFE;
			pwrinfo24g->ofdm_diff[rfpath][txcnt] = 0xFE;
		}
	}
}