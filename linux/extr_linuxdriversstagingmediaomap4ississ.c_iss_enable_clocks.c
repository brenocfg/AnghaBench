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
struct iss_device {int /*<<< orphan*/  iss_fck; int /*<<< orphan*/  dev; int /*<<< orphan*/  iss_ctrlclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int iss_enable_clocks(struct iss_device *iss)
{
	int ret;

	ret = clk_enable(iss->iss_fck);
	if (ret) {
		dev_err(iss->dev, "clk_enable iss_fck failed\n");
		return ret;
	}

	ret = clk_enable(iss->iss_ctrlclk);
	if (ret) {
		dev_err(iss->dev, "clk_enable iss_ctrlclk failed\n");
		clk_disable(iss->iss_fck);
		return ret;
	}

	return 0;
}