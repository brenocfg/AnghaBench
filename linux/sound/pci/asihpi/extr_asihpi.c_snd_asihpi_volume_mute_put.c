#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int HPI_BITMASK_ALL_CHANNELS ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_volume_set_mute (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_asihpi_volume_mute_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	u32 h_control = kcontrol->private_value;
	/* HPI currently only supports all or none muting of multichannel volume
	ALSA Switch element has opposite sense to HPI mute: on==unmuted, off=muted
	*/
	int mute =  ucontrol->value.integer.value[0] ? 0 : HPI_BITMASK_ALL_CHANNELS;
	hpi_handle_error(hpi_volume_set_mute(h_control, mute));
	return 1;
}