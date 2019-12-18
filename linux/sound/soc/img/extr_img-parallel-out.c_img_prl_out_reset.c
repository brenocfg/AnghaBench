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
typedef  int u32 ;
struct img_prl_out {int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_PRL_OUT_CTL ; 
 int IMG_PRL_OUT_CTL_ME_MASK ; 
 int img_prl_out_readl (struct img_prl_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_prl_out_writel (struct img_prl_out*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_prl_out_reset(struct img_prl_out *prl)
{
	u32 ctl;

	ctl = img_prl_out_readl(prl, IMG_PRL_OUT_CTL) &
			~IMG_PRL_OUT_CTL_ME_MASK;

	reset_control_assert(prl->rst);
	reset_control_deassert(prl->rst);

	img_prl_out_writel(prl, ctl, IMG_PRL_OUT_CTL);
}