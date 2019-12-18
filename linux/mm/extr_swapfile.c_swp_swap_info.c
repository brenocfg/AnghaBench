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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int dummy; } ;

/* Variables and functions */
 struct swap_info_struct* swap_type_to_swap_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_type (int /*<<< orphan*/ ) ; 

struct swap_info_struct *swp_swap_info(swp_entry_t entry)
{
	return swap_type_to_swap_info(swp_type(entry));
}