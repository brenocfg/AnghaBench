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
struct wil6210_priv {int /*<<< orphan*/  rx_buf_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL_EDMA_RX_BUF_LEN_DEFAULT ; 
 int /*<<< orphan*/  WIL_MAX_ETH_MTU ; 
 scalar_t__ rx_large_buf ; 

__attribute__((used)) static void wil_rx_buf_len_init_edma(struct wil6210_priv *wil)
{
	wil->rx_buf_len = rx_large_buf ?
		WIL_MAX_ETH_MTU : WIL_EDMA_RX_BUF_LEN_DEFAULT;
}