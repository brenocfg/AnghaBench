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
struct xonar_wm87x6 {int /*<<< orphan*/  hdmi; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm8776_registers_init (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_hdmi_resume (struct oxygen*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xonar_hdav_slim_resume(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	wm8776_registers_init(chip);
	xonar_hdmi_resume(chip, &data->hdmi);
	xonar_enable_output(chip);
}