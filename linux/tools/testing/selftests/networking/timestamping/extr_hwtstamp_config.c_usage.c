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

/* Variables and functions */
 int /*<<< orphan*/  N_RX_FILTERS ; 
 int /*<<< orphan*/  N_TX_TYPES ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_filters ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tx_types ; 

__attribute__((used)) static void usage(void)
{
	fputs("Usage: hwtstamp_config if_name [tx_type rx_filter]\n"
	      "tx_type is any of (case-insensitive):\n",
	      stderr);
	list_names(stderr, tx_types, N_TX_TYPES);
	fputs("rx_filter is any of (case-insensitive):\n", stderr);
	list_names(stderr, rx_filters, N_RX_FILTERS);
}