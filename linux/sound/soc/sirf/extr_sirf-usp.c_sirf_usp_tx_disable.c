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
struct sirf_usp {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  USP_TX_ENA ; 
 int /*<<< orphan*/  USP_TX_FIFO_OP ; 
 int /*<<< orphan*/  USP_TX_RX_ENABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sirf_usp_tx_disable(struct sirf_usp *usp)
{
	regmap_update_bits(usp->regmap, USP_TX_RX_ENABLE,
		USP_TX_ENA, ~USP_TX_ENA);
	/* FIFO stop */
	regmap_write(usp->regmap, USP_TX_FIFO_OP, 0);
}