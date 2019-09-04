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
struct wil6210_priv {int rx_max_burst_duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGF_INT_COUNT_ON_SPECIAL_EVT ; 
 int /*<<< orphan*/  RGF_INT_CTRL_INT_GEN_CFG_0 ; 
 int /*<<< orphan*/  RGF_INT_CTRL_INT_GEN_CFG_1 ; 
 int /*<<< orphan*/  RGF_INT_GEN_IDLE_TIME_LIMIT ; 
 int /*<<< orphan*/  RGF_INT_GEN_TIME_UNIT_LIMIT ; 
 int WIL_EDMA_AGG_WATERMARK ; 
 int WIL_EDMA_AGG_WATERMARK_POS ; 
 int WIL_EDMA_IDLE_TIME_LIMIT_USEC ; 
 int WIL_EDMA_TIME_UNIT_CLK_CYCLES ; 
 int /*<<< orphan*/  wil_c (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wil_s (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wil_w (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 

void wil_configure_interrupt_moderation_edma(struct wil6210_priv *wil)
{
	u32 moderation;

	wil_s(wil, RGF_INT_GEN_IDLE_TIME_LIMIT, WIL_EDMA_IDLE_TIME_LIMIT_USEC);

	wil_s(wil, RGF_INT_GEN_TIME_UNIT_LIMIT, WIL_EDMA_TIME_UNIT_CLK_CYCLES);

	/* Update RX and TX moderation */
	moderation = wil->rx_max_burst_duration |
		(WIL_EDMA_AGG_WATERMARK << WIL_EDMA_AGG_WATERMARK_POS);
	wil_w(wil, RGF_INT_CTRL_INT_GEN_CFG_0, moderation);
	wil_w(wil, RGF_INT_CTRL_INT_GEN_CFG_1, moderation);

	/* Treat special events as regular
	 * (set bit 0 to 0x1 and clear bits 1-8)
	 */
	wil_c(wil, RGF_INT_COUNT_ON_SPECIAL_EVT, 0x1FE);
	wil_s(wil, RGF_INT_COUNT_ON_SPECIAL_EVT, 0x1);
}