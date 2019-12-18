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
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  special_dig_out_iface_labels ; 

__attribute__((used)) static int special_dig_out_iface_ctl_info(struct snd_kcontrol *kctl,
					  struct snd_ctl_elem_info *einf)
{
	return snd_ctl_enum_info(einf, 1,
				 ARRAY_SIZE(special_dig_out_iface_labels),
				 special_dig_out_iface_labels);
}