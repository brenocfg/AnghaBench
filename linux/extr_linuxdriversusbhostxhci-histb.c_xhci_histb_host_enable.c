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
struct xhci_hcd_histb {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  utmi_clk; int /*<<< orphan*/  pipe_clk; int /*<<< orphan*/  soft_reset; int /*<<< orphan*/  dev; int /*<<< orphan*/  suspend_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_histb_host_enable(struct xhci_hcd_histb *histb)
{
	int ret;

	ret = clk_prepare_enable(histb->bus_clk);
	if (ret) {
		dev_err(histb->dev, "failed to enable bus clk\n");
		return ret;
	}

	ret = clk_prepare_enable(histb->utmi_clk);
	if (ret) {
		dev_err(histb->dev, "failed to enable utmi clk\n");
		goto err_utmi_clk;
	}

	ret = clk_prepare_enable(histb->pipe_clk);
	if (ret) {
		dev_err(histb->dev, "failed to enable pipe clk\n");
		goto err_pipe_clk;
	}

	ret = clk_prepare_enable(histb->suspend_clk);
	if (ret) {
		dev_err(histb->dev, "failed to enable suspend clk\n");
		goto err_suspend_clk;
	}

	reset_control_deassert(histb->soft_reset);

	return 0;

err_suspend_clk:
	clk_disable_unprepare(histb->pipe_clk);
err_pipe_clk:
	clk_disable_unprepare(histb->utmi_clk);
err_utmi_clk:
	clk_disable_unprepare(histb->bus_clk);

	return ret;
}