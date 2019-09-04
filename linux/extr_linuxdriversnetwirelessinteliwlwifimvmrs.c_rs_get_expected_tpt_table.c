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
typedef  int /*<<< orphan*/  u16 ;
struct rs_tx_column {scalar_t__ mode; scalar_t__ sgi; } ;
struct iwl_lq_sta {scalar_t__ is_agg; } ;

/* Variables and functions */
 int IWL_RATE_COUNT ; 
#define  RATE_MCS_CHAN_WIDTH_160 131 
#define  RATE_MCS_CHAN_WIDTH_20 130 
#define  RATE_MCS_CHAN_WIDTH_40 129 
#define  RATE_MCS_CHAN_WIDTH_80 128 
 scalar_t__ RS_LEGACY ; 
 scalar_t__ RS_MIMO2 ; 
 scalar_t__ RS_SISO ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  const* expected_tpt_legacy ; 
 int /*<<< orphan*/ ** expected_tpt_mimo2_160MHz ; 
 int /*<<< orphan*/ ** expected_tpt_mimo2_20MHz ; 
 int /*<<< orphan*/ ** expected_tpt_mimo2_40MHz ; 
 int /*<<< orphan*/ ** expected_tpt_mimo2_80MHz ; 
 int /*<<< orphan*/ ** expected_tpt_siso_160MHz ; 
 int /*<<< orphan*/ ** expected_tpt_siso_20MHz ; 
 int /*<<< orphan*/ ** expected_tpt_siso_40MHz ; 
 int /*<<< orphan*/ ** expected_tpt_siso_80MHz ; 

__attribute__((used)) static const u16 *rs_get_expected_tpt_table(struct iwl_lq_sta *lq_sta,
					    const struct rs_tx_column *column,
					    u32 bw)
{
	/* Used to choose among HT tables */
	const u16 (*ht_tbl_pointer)[IWL_RATE_COUNT];

	if (WARN_ON_ONCE(column->mode != RS_LEGACY &&
			 column->mode != RS_SISO &&
			 column->mode != RS_MIMO2))
		return expected_tpt_legacy;

	/* Legacy rates have only one table */
	if (column->mode == RS_LEGACY)
		return expected_tpt_legacy;

	ht_tbl_pointer = expected_tpt_mimo2_20MHz;
	/* Choose among many HT tables depending on number of streams
	 * (SISO/MIMO2), channel width (20/40/80), SGI, and aggregation
	 * status */
	if (column->mode == RS_SISO) {
		switch (bw) {
		case RATE_MCS_CHAN_WIDTH_20:
			ht_tbl_pointer = expected_tpt_siso_20MHz;
			break;
		case RATE_MCS_CHAN_WIDTH_40:
			ht_tbl_pointer = expected_tpt_siso_40MHz;
			break;
		case RATE_MCS_CHAN_WIDTH_80:
			ht_tbl_pointer = expected_tpt_siso_80MHz;
			break;
		case RATE_MCS_CHAN_WIDTH_160:
			ht_tbl_pointer = expected_tpt_siso_160MHz;
			break;
		default:
			WARN_ON_ONCE(1);
		}
	} else if (column->mode == RS_MIMO2) {
		switch (bw) {
		case RATE_MCS_CHAN_WIDTH_20:
			ht_tbl_pointer = expected_tpt_mimo2_20MHz;
			break;
		case RATE_MCS_CHAN_WIDTH_40:
			ht_tbl_pointer = expected_tpt_mimo2_40MHz;
			break;
		case RATE_MCS_CHAN_WIDTH_80:
			ht_tbl_pointer = expected_tpt_mimo2_80MHz;
			break;
		case RATE_MCS_CHAN_WIDTH_160:
			ht_tbl_pointer = expected_tpt_mimo2_160MHz;
			break;
		default:
			WARN_ON_ONCE(1);
		}
	} else {
		WARN_ON_ONCE(1);
	}

	if (!column->sgi && !lq_sta->is_agg)		/* Normal */
		return ht_tbl_pointer[0];
	else if (column->sgi && !lq_sta->is_agg)        /* SGI */
		return ht_tbl_pointer[1];
	else if (!column->sgi && lq_sta->is_agg)        /* AGG */
		return ht_tbl_pointer[2];
	else						/* AGG+SGI */
		return ht_tbl_pointer[3];
}