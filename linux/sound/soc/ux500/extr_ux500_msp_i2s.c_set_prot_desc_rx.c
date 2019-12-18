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
struct ux500_msp {scalar_t__ registers; scalar_t__ def_elem_len; } ;
struct msp_protdesc {int rx_elem_len_1; int rx_elem_len_2; int /*<<< orphan*/  frame_sync_ignore; int /*<<< orphan*/  expansion_mode; int /*<<< orphan*/  rx_half_word_swap; int /*<<< orphan*/  rx_fsync_pol; int /*<<< orphan*/  rx_byte_order; int /*<<< orphan*/  rx_data_delay; int /*<<< orphan*/  rx_frame_len_2; int /*<<< orphan*/  rx_frame_len_1; int /*<<< orphan*/  rx_phase2_start_mode; int /*<<< orphan*/  rx_phase_mode; } ;
typedef  enum msp_data_size { ____Placeholder_msp_data_size } msp_data_size ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_DATA_DELAY_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_DATA_WORD_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_FSYNC_POL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_P1_ELEM_LEN_BITS (int) ; 
 int /*<<< orphan*/  MSP_P1_FRAME_LEN_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_P2_ELEM_LEN_BITS (int) ; 
 int /*<<< orphan*/  MSP_P2_ENABLE_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_P2_FRAME_LEN_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_P2_START_MODE_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ MSP_RCF ; 
 int /*<<< orphan*/  MSP_SET_COMPANDING_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_SET_ENDIANNES_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_SET_FSYNC_IGNORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void set_prot_desc_rx(struct ux500_msp *msp,
			struct msp_protdesc *protdesc,
			enum msp_data_size data_size)
{
	u32 temp_reg = 0;

	temp_reg |= MSP_P2_ENABLE_BIT(protdesc->rx_phase_mode);
	temp_reg |= MSP_P2_START_MODE_BIT(protdesc->rx_phase2_start_mode);
	temp_reg |= MSP_P1_FRAME_LEN_BITS(protdesc->rx_frame_len_1);
	temp_reg |= MSP_P2_FRAME_LEN_BITS(protdesc->rx_frame_len_2);
	if (msp->def_elem_len) {
		temp_reg |= MSP_P1_ELEM_LEN_BITS(protdesc->rx_elem_len_1);
		temp_reg |= MSP_P2_ELEM_LEN_BITS(protdesc->rx_elem_len_2);
	} else {
		temp_reg |= MSP_P1_ELEM_LEN_BITS(data_size);
		temp_reg |= MSP_P2_ELEM_LEN_BITS(data_size);
	}

	temp_reg |= MSP_DATA_DELAY_BITS(protdesc->rx_data_delay);
	temp_reg |= MSP_SET_ENDIANNES_BIT(protdesc->rx_byte_order);
	temp_reg |= MSP_FSYNC_POL(protdesc->rx_fsync_pol);
	temp_reg |= MSP_DATA_WORD_SWAP(protdesc->rx_half_word_swap);
	temp_reg |= MSP_SET_COMPANDING_MODE(protdesc->expansion_mode);
	temp_reg |= MSP_SET_FSYNC_IGNORE(protdesc->frame_sync_ignore);

	writel(temp_reg, msp->registers + MSP_RCF);
}