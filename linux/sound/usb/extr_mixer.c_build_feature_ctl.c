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
struct usb_audio_term {int dummy; } ;
struct uac_feature_unit_descriptor {int dummy; } ;
struct mixer_build {int /*<<< orphan*/  oterm; int /*<<< orphan*/  map; int /*<<< orphan*/  mixer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __build_feature_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,struct usb_audio_term*,int /*<<< orphan*/ *,int,int,int) ; 
 int uac_feature_unit_iFeature (struct uac_feature_unit_descriptor*) ; 

__attribute__((used)) static void build_feature_ctl(struct mixer_build *state, void *raw_desc,
			      unsigned int ctl_mask, int control,
			      struct usb_audio_term *iterm, int unitid,
			      int readonly_mask)
{
	struct uac_feature_unit_descriptor *desc = raw_desc;
	int nameid = uac_feature_unit_iFeature(desc);

	__build_feature_ctl(state->mixer, state->map, ctl_mask, control,
			iterm, &state->oterm, unitid, nameid, readonly_mask);
}