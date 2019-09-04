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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WM8996_MICD_BIAS_STARTTIME_MASK ; 
 int WM8996_MICD_BIAS_STARTTIME_SHIFT ; 
 int WM8996_MICD_RATE_MASK ; 
 int WM8996_MICD_RATE_SHIFT ; 
 int /*<<< orphan*/  WM8996_MIC_DETECT_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm8996_hpdet_start (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8996_report_headphone(struct snd_soc_component *component)
{
	dev_dbg(component->dev, "Headphone detected\n");
	wm8996_hpdet_start(component);

	/* Increase the detection rate a bit for responsiveness. */
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1,
			    WM8996_MICD_RATE_MASK |
			    WM8996_MICD_BIAS_STARTTIME_MASK,
			    7 << WM8996_MICD_RATE_SHIFT |
			    7 << WM8996_MICD_BIAS_STARTTIME_SHIFT);
}