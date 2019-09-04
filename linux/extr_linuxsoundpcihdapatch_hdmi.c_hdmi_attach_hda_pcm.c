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
struct hdmi_spec_per_pin {int pcm_idx; int /*<<< orphan*/  pcm; } ;
struct hdmi_spec {int /*<<< orphan*/  pcm_bitmap; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  get_hdmi_pcm (struct hdmi_spec*,int) ; 
 int hdmi_find_pcm_slot (struct hdmi_spec*,struct hdmi_spec_per_pin*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_attach_hda_pcm(struct hdmi_spec *spec,
				struct hdmi_spec_per_pin *per_pin)
{
	int idx;

	/* pcm already be attached to the pin */
	if (per_pin->pcm)
		return;
	idx = hdmi_find_pcm_slot(spec, per_pin);
	if (idx == -EBUSY)
		return;
	per_pin->pcm_idx = idx;
	per_pin->pcm = get_hdmi_pcm(spec, idx);
	set_bit(idx, &spec->pcm_bitmap);
}