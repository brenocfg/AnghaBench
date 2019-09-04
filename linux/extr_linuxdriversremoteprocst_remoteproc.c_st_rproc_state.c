#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_rproc {int /*<<< orphan*/  pwr_reset; TYPE_1__* config; int /*<<< orphan*/  sw_reset; } ;
struct rproc {struct st_rproc* priv; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ pwr_reset; scalar_t__ sw_reset; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rproc* platform_get_drvdata (struct platform_device*) ; 
 int reset_control_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_rproc_state(struct platform_device *pdev)
{
	struct rproc *rproc = platform_get_drvdata(pdev);
	struct st_rproc *ddata = rproc->priv;
	int reset_sw = 0, reset_pwr = 0;

	if (ddata->config->sw_reset)
		reset_sw = reset_control_status(ddata->sw_reset);

	if (ddata->config->pwr_reset)
		reset_pwr = reset_control_status(ddata->pwr_reset);

	if (reset_sw < 0 || reset_pwr < 0)
		return -EINVAL;

	return !reset_sw && !reset_pwr;
}