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
struct wm_adsp {int /*<<< orphan*/  boot_work; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp_boot_work ; 
 int wm_adsp_common_init (struct wm_adsp*) ; 
 int /*<<< orphan*/  wm_halo_ops ; 

int wm_halo_init(struct wm_adsp *dsp)
{
	int ret;

	ret = wm_adsp_common_init(dsp);
	if (ret)
		return ret;

	dsp->ops = &wm_halo_ops;

	INIT_WORK(&dsp->boot_work, wm_adsp_boot_work);

	return 0;
}