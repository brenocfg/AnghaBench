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
typedef  int /*<<< orphan*/ * usb_mixer_elem_resume_func_t ;
struct usb_mixer_interface {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int add_single_ctl_with_resume (struct usb_mixer_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snd_microii_mixer_spdif ; 
#define  snd_microii_spdif_default_update 129 
#define  snd_microii_spdif_switch_update 128 

__attribute__((used)) static int snd_microii_controls_create(struct usb_mixer_interface *mixer)
{
	int err, i;
	static usb_mixer_elem_resume_func_t resume_funcs[] = {
		snd_microii_spdif_default_update,
		NULL,
		snd_microii_spdif_switch_update
	};

	for (i = 0; i < ARRAY_SIZE(snd_microii_mixer_spdif); ++i) {
		err = add_single_ctl_with_resume(mixer, 0,
						 resume_funcs[i],
						 &snd_microii_mixer_spdif[i],
						 NULL);
		if (err < 0)
			return err;
	}

	return 0;
}