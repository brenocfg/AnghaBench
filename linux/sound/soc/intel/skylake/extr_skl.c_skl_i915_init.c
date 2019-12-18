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
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_CODEC_IDX_CONTROLLER ; 
 int /*<<< orphan*/  snd_hdac_display_power (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 int snd_hdac_i915_init (struct hdac_bus*) ; 

__attribute__((used)) static int skl_i915_init(struct hdac_bus *bus)
{
	int err;

	/*
	 * The HDMI codec is in GPU so we need to ensure that it is powered
	 * up and ready for probe
	 */
	err = snd_hdac_i915_init(bus);
	if (err < 0)
		return err;

	snd_hdac_display_power(bus, HDA_CODEC_IDX_CONTROLLER, true);

	return 0;
}