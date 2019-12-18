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
struct hdmi_spec_per_pin {int pcm_idx; int /*<<< orphan*/ * pcm; } ;
struct hdmi_spec {int pcm_used; int /*<<< orphan*/  pcm_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_detach_hda_pcm(struct hdmi_spec *spec,
				struct hdmi_spec_per_pin *per_pin)
{
	int idx;

	/* pcm already be detached from the pin */
	if (!per_pin->pcm)
		return;
	idx = per_pin->pcm_idx;
	per_pin->pcm_idx = -1;
	per_pin->pcm = NULL;
	if (idx >= 0 && idx < spec->pcm_used)
		clear_bit(idx, &spec->pcm_bitmap);
}