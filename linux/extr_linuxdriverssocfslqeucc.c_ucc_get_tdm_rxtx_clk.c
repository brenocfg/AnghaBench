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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum qe_clock { ____Placeholder_qe_clock } qe_clock ;
typedef  enum comm_dir { ____Placeholder_comm_dir } comm_dir ;

/* Variables and functions */
 int COMM_DIR_RX ; 
 int COMM_DIR_TX ; 
 int ucc_get_tdm_common_clk (int /*<<< orphan*/ ,int) ; 
 int ucc_get_tdm_rx_clk (int /*<<< orphan*/ ,int) ; 
 int ucc_get_tdm_tx_clk (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ucc_get_tdm_rxtx_clk(enum comm_dir mode, u32 tdm_num,
				enum qe_clock clock)
{
	int clock_bits;

	clock_bits = ucc_get_tdm_common_clk(tdm_num, clock);
	if (clock_bits > 0)
		return clock_bits;
	if (mode == COMM_DIR_RX)
		clock_bits = ucc_get_tdm_rx_clk(tdm_num, clock);
	if (mode == COMM_DIR_TX)
		clock_bits = ucc_get_tdm_tx_clk(tdm_num, clock);
	return clock_bits;
}