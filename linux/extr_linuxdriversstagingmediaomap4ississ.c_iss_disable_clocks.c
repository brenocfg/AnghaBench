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
struct iss_device {int /*<<< orphan*/  iss_fck; int /*<<< orphan*/  iss_ctrlclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iss_disable_clocks(struct iss_device *iss)
{
	clk_disable(iss->iss_ctrlclk);
	clk_disable(iss->iss_fck);
}