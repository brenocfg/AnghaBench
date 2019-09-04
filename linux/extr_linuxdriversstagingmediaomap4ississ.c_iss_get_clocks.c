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
struct iss_device {void* iss_ctrlclk; int /*<<< orphan*/  dev; void* iss_fck; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int iss_get_clocks(struct iss_device *iss)
{
	iss->iss_fck = devm_clk_get(iss->dev, "iss_fck");
	if (IS_ERR(iss->iss_fck)) {
		dev_err(iss->dev, "Unable to get iss_fck clock info\n");
		return PTR_ERR(iss->iss_fck);
	}

	iss->iss_ctrlclk = devm_clk_get(iss->dev, "iss_ctrlclk");
	if (IS_ERR(iss->iss_ctrlclk)) {
		dev_err(iss->dev, "Unable to get iss_ctrlclk clock info\n");
		return PTR_ERR(iss->iss_ctrlclk);
	}

	return 0;
}