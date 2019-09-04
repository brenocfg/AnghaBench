#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  genpd; } ;

/* Variables and functions */
 int meson_gx_pwrc_vpu_get_power (TYPE_1__*) ; 
 int /*<<< orphan*/  meson_gx_pwrc_vpu_power_off (int /*<<< orphan*/ *) ; 
 TYPE_1__ vpu_hdmi_pd ; 

__attribute__((used)) static void meson_gx_pwrc_vpu_shutdown(struct platform_device *pdev)
{
	bool powered_off;

	powered_off = meson_gx_pwrc_vpu_get_power(&vpu_hdmi_pd);
	if (!powered_off)
		meson_gx_pwrc_vpu_power_off(&vpu_hdmi_pd.genpd);
}