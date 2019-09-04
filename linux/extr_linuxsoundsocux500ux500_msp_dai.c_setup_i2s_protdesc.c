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
struct msp_protdesc {int rx_fsync_pol; int /*<<< orphan*/  frame_sync_ignore; int /*<<< orphan*/  expansion_mode; int /*<<< orphan*/  compression_mode; void* rx_half_word_swap; void* tx_half_word_swap; void* tx_data_delay; void* rx_data_delay; int /*<<< orphan*/  tx_clk_pol; int /*<<< orphan*/  rx_clk_pol; void* tx_elem_len_2; void* tx_elem_len_1; void* rx_elem_len_2; void* rx_elem_len_1; void* tx_frame_len_2; void* tx_frame_len_1; void* rx_frame_len_2; void* rx_frame_len_1; int /*<<< orphan*/  tx_fsync_pol; void* tx_byte_order; void* rx_byte_order; void* tx_phase2_start_mode; void* rx_phase2_start_mode; void* tx_phase_mode; void* rx_phase_mode; } ;

/* Variables and functions */
 void* MSP_BTF_MS_BIT_FIRST ; 
 int /*<<< orphan*/  MSP_COMPRESS_MODE_LINEAR ; 
 void* MSP_DELAY_0 ; 
 void* MSP_DUAL_PHASE ; 
 void* MSP_ELEM_LEN_16 ; 
 int /*<<< orphan*/  MSP_EXPAND_MODE_LINEAR ; 
 int /*<<< orphan*/  MSP_FALLING_EDGE ; 
 void* MSP_FRAME_LEN_1 ; 
 int /*<<< orphan*/  MSP_FSYNC_IGNORE ; 
 int /*<<< orphan*/  MSP_FSYNC_POL (int) ; 
 int MSP_FSYNC_POL_ACT_LO ; 
 void* MSP_PHASE2_START_MODE_FSYNC ; 
 int /*<<< orphan*/  MSP_RISING_EDGE ; 
 void* MSP_SWAP_NONE ; 
 int RFSPOL_SHIFT ; 

__attribute__((used)) static int setup_i2s_protdesc(struct msp_protdesc *prot_desc)
{
	prot_desc->rx_phase_mode = MSP_DUAL_PHASE;
	prot_desc->tx_phase_mode = MSP_DUAL_PHASE;
	prot_desc->rx_phase2_start_mode = MSP_PHASE2_START_MODE_FSYNC;
	prot_desc->tx_phase2_start_mode = MSP_PHASE2_START_MODE_FSYNC;
	prot_desc->rx_byte_order = MSP_BTF_MS_BIT_FIRST;
	prot_desc->tx_byte_order = MSP_BTF_MS_BIT_FIRST;
	prot_desc->tx_fsync_pol = MSP_FSYNC_POL(MSP_FSYNC_POL_ACT_LO);
	prot_desc->rx_fsync_pol = MSP_FSYNC_POL_ACT_LO << RFSPOL_SHIFT;

	prot_desc->rx_frame_len_1 = MSP_FRAME_LEN_1;
	prot_desc->rx_frame_len_2 = MSP_FRAME_LEN_1;
	prot_desc->tx_frame_len_1 = MSP_FRAME_LEN_1;
	prot_desc->tx_frame_len_2 = MSP_FRAME_LEN_1;
	prot_desc->rx_elem_len_1 = MSP_ELEM_LEN_16;
	prot_desc->rx_elem_len_2 = MSP_ELEM_LEN_16;
	prot_desc->tx_elem_len_1 = MSP_ELEM_LEN_16;
	prot_desc->tx_elem_len_2 = MSP_ELEM_LEN_16;

	prot_desc->rx_clk_pol = MSP_RISING_EDGE;
	prot_desc->tx_clk_pol = MSP_FALLING_EDGE;

	prot_desc->rx_data_delay = MSP_DELAY_0;
	prot_desc->tx_data_delay = MSP_DELAY_0;

	prot_desc->tx_half_word_swap = MSP_SWAP_NONE;
	prot_desc->rx_half_word_swap = MSP_SWAP_NONE;
	prot_desc->compression_mode = MSP_COMPRESS_MODE_LINEAR;
	prot_desc->expansion_mode = MSP_EXPAND_MODE_LINEAR;
	prot_desc->frame_sync_ignore = MSP_FSYNC_IGNORE;

	return 0;
}