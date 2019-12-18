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
struct wm_adsp {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm_adsp1_ops ; 
 int wm_adsp_common_init (struct wm_adsp*) ; 

int wm_adsp1_init(struct wm_adsp *dsp)
{
	dsp->ops = &wm_adsp1_ops;

	return wm_adsp_common_init(dsp);
}