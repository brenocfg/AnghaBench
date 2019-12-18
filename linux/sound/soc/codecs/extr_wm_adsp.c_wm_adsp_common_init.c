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
struct wm_adsp {int /*<<< orphan*/  pwr_lock; int /*<<< orphan*/  buffer_list; int /*<<< orphan*/  compr_list; int /*<<< orphan*/  ctl_list; int /*<<< orphan*/  alg_regions; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int wm_adsp_create_name (struct wm_adsp*) ; 

__attribute__((used)) static int wm_adsp_common_init(struct wm_adsp *dsp)
{
	int ret;

	ret = wm_adsp_create_name(dsp);
	if (ret)
		return ret;

	INIT_LIST_HEAD(&dsp->alg_regions);
	INIT_LIST_HEAD(&dsp->ctl_list);
	INIT_LIST_HEAD(&dsp->compr_list);
	INIT_LIST_HEAD(&dsp->buffer_list);

	mutex_init(&dsp->pwr_lock);

	return 0;
}