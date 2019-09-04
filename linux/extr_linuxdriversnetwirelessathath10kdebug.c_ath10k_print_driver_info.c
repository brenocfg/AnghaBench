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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_debug_print_board_info (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_debug_print_boot_info (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_debug_print_hwfw_info (struct ath10k*) ; 

void ath10k_print_driver_info(struct ath10k *ar)
{
	ath10k_debug_print_hwfw_info(ar);
	ath10k_debug_print_board_info(ar);
	ath10k_debug_print_boot_info(ar);
}