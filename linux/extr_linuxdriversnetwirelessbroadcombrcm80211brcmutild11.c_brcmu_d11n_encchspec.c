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
struct brcmu_chan {scalar_t__ bw; scalar_t__ chnum; int /*<<< orphan*/  chspec; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 scalar_t__ BRCMU_CHAN_BW_20 ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_NONE ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_CH_MASK ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_CH_SHIFT ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_BND_2G ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_BND_5G ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_BW_MASK ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_SB_MASK ; 
 scalar_t__ CH_MAX_2G_CHANNEL ; 
 int /*<<< orphan*/  brcmu_maskset16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ d11n_bw (scalar_t__) ; 
 scalar_t__ d11n_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmu_d11n_encchspec(struct brcmu_chan *ch)
{
	if (ch->bw == BRCMU_CHAN_BW_20)
		ch->sb = BRCMU_CHAN_SB_NONE;

	ch->chspec = 0;
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_CH_MASK,
			BRCMU_CHSPEC_CH_SHIFT, ch->chnum);
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11N_SB_MASK,
			0, d11n_sb(ch->sb));
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11N_BW_MASK,
			0, d11n_bw(ch->bw));

	if (ch->chnum <= CH_MAX_2G_CHANNEL)
		ch->chspec |= BRCMU_CHSPEC_D11N_BND_2G;
	else
		ch->chspec |= BRCMU_CHSPEC_D11N_BND_5G;
}