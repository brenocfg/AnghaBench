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
struct s3c_pcm_info {int /*<<< orphan*/  pclk; int /*<<< orphan*/  cclk; } ;
struct platform_device {size_t id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct s3c_pcm_info* s3c_pcm ; 

__attribute__((used)) static int s3c_pcm_dev_remove(struct platform_device *pdev)
{
	struct s3c_pcm_info *pcm = &s3c_pcm[pdev->id];

	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(pcm->cclk);
	clk_disable_unprepare(pcm->pclk);

	return 0;
}