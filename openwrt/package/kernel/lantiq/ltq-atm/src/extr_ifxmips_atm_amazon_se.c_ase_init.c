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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_share_buffer () ; 
 int /*<<< orphan*/  init_atm_tc () ; 
 int /*<<< orphan*/  init_ema () ; 
 int /*<<< orphan*/  init_mailbox () ; 
 int /*<<< orphan*/  init_pmu () ; 
 int /*<<< orphan*/  reset_ppe (struct platform_device*) ; 

void ase_init(struct platform_device *pdev)
{
    init_pmu();

    reset_ppe(pdev);

    init_ema();

    init_mailbox();

    init_atm_tc();

    clear_share_buffer();
}