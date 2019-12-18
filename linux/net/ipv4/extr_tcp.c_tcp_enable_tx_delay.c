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
 scalar_t__ cmpxchg (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_tx_delay_enabled ; 

__attribute__((used)) static void tcp_enable_tx_delay(void)
{
	if (!static_branch_unlikely(&tcp_tx_delay_enabled)) {
		static int __tcp_tx_delay_enabled = 0;

		if (cmpxchg(&__tcp_tx_delay_enabled, 0, 1) == 0) {
			static_branch_enable(&tcp_tx_delay_enabled);
			pr_info("TCP_TX_DELAY enabled\n");
		}
	}
}