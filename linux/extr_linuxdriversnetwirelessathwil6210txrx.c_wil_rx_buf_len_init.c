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
struct wil6210_priv {scalar_t__ rx_buf_len; } ;

/* Variables and functions */
 scalar_t__ TXRX_BUF_LEN_DEFAULT ; 
 scalar_t__ WIL_MAX_ETH_MTU ; 
 scalar_t__ WIL_MAX_MPDU_OVERHEAD ; 
 scalar_t__ mtu_max ; 
 scalar_t__ rx_large_buf ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,scalar_t__) ; 

__attribute__((used)) static void wil_rx_buf_len_init(struct wil6210_priv *wil)
{
	wil->rx_buf_len = rx_large_buf ?
		WIL_MAX_ETH_MTU : TXRX_BUF_LEN_DEFAULT - WIL_MAX_MPDU_OVERHEAD;
	if (mtu_max > wil->rx_buf_len) {
		/* do not allow RX buffers to be smaller than mtu_max, for
		 * backward compatibility (mtu_max parameter was also used
		 * to support receiving large packets)
		 */
		wil_info(wil, "Override RX buffer to mtu_max(%d)\n", mtu_max);
		wil->rx_buf_len = mtu_max;
	}
}