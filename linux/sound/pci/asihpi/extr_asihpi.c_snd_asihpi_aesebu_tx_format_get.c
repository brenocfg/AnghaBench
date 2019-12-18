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

/* Variables and functions */
 int /*<<< orphan*/  hpi_aesebu_transmitter_get_format ; 
 int snd_asihpi_aesebu_format_get (struct snd_kcontrol*,struct snd_ctl_elem_value*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_asihpi_aesebu_tx_format_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol) {
	return snd_asihpi_aesebu_format_get(kcontrol, ucontrol,
					hpi_aesebu_transmitter_get_format);
}