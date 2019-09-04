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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct mwifiex_private {int /*<<< orphan*/  tx_ba_stream_tbl_ptr; } ;
struct mwifiex_adapter {size_t priv_num; scalar_t__ fw_api_ver; int /*<<< orphan*/  hw_dot_11n_dev_cap; struct mwifiex_private** priv; } ;

/* Variables and functions */
 scalar_t__ GETSUPP_TXBASTREAMS (int /*<<< orphan*/ ) ; 
 scalar_t__ MWIFIEX_FW_V15 ; 
 scalar_t__ MWIFIEX_MAX_TX_BASTREAM_SUPPORTED ; 
 scalar_t__ mwifiex_wmm_list_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u8 mwifiex_space_avail_for_new_ba_stream(
					struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;
	u8 i;
	u32 ba_stream_num = 0, ba_stream_max;

	ba_stream_max = MWIFIEX_MAX_TX_BASTREAM_SUPPORTED;

	for (i = 0; i < adapter->priv_num; i++) {
		priv = adapter->priv[i];
		if (priv)
			ba_stream_num += mwifiex_wmm_list_len(
				&priv->tx_ba_stream_tbl_ptr);
	}

	if (adapter->fw_api_ver == MWIFIEX_FW_V15) {
		ba_stream_max =
			       GETSUPP_TXBASTREAMS(adapter->hw_dot_11n_dev_cap);
		if (!ba_stream_max)
			ba_stream_max = MWIFIEX_MAX_TX_BASTREAM_SUPPORTED;
	}

	return ((ba_stream_num < ba_stream_max) ? true : false);
}