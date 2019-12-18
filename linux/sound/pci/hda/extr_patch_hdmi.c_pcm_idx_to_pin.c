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
struct hdmi_spec_per_pin {int pcm_idx; } ;
struct hdmi_spec {int num_pins; } ;

/* Variables and functions */
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 

__attribute__((used)) static struct hdmi_spec_per_pin *pcm_idx_to_pin(struct hdmi_spec *spec,
						int pcm_idx)
{
	int i;
	struct hdmi_spec_per_pin *per_pin;

	for (i = 0; i < spec->num_pins; i++) {
		per_pin = get_pin(spec, i);
		if (per_pin->pcm_idx == pcm_idx)
			return per_pin;
	}
	return NULL;
}