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
struct hdmi_spec_per_pin {scalar_t__ pcm_idx; int chmap_set; int setup; scalar_t__ channels; int /*<<< orphan*/  chmap; int /*<<< orphan*/  codec; } ;
struct hdmi_spec {scalar_t__ pcm_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_spdif_ctls_unassign (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hdmi_pcm_reset_pin(struct hdmi_spec *spec,
			   struct hdmi_spec_per_pin *per_pin)
{
	if (per_pin->pcm_idx >= 0 && per_pin->pcm_idx < spec->pcm_used)
		snd_hda_spdif_ctls_unassign(per_pin->codec, per_pin->pcm_idx);

	per_pin->chmap_set = false;
	memset(per_pin->chmap, 0, sizeof(per_pin->chmap));

	per_pin->setup = false;
	per_pin->channels = 0;
}