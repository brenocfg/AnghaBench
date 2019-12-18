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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxt_update_headset_mode (struct hda_codec*) ; 

__attribute__((used)) static void cxt_update_headset_mode_hook(struct hda_codec *codec,
					 struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	cxt_update_headset_mode(codec);
}