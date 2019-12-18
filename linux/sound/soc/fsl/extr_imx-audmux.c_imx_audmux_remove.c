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
 scalar_t__ IMX31_AUDMUX ; 
 int /*<<< orphan*/  audmux_debugfs_remove () ; 
 scalar_t__ audmux_type ; 

__attribute__((used)) static int imx_audmux_remove(struct platform_device *pdev)
{
	if (audmux_type == IMX31_AUDMUX)
		audmux_debugfs_remove();

	return 0;
}