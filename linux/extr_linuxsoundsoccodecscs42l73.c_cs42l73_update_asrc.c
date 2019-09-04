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
typedef  int u8 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
#define  CS42L73_ASP 130 
 int /*<<< orphan*/  CS42L73_ASPC ; 
#define  CS42L73_VSP 129 
 int /*<<< orphan*/  CS42L73_VXSPFS ; 
#define  CS42L73_XSP 128 
 int cs42l73_get_xspfs_coeff (int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cs42l73_update_asrc(struct snd_soc_component *component, int id, int srate)
{
	u8 spfs = 0;

	if (srate > 0)
		spfs = cs42l73_get_xspfs_coeff(srate);

	switch (id) {
	case CS42L73_XSP:
		snd_soc_component_update_bits(component, CS42L73_VXSPFS, 0x0f, spfs);
	break;
	case CS42L73_ASP:
		snd_soc_component_update_bits(component, CS42L73_ASPC, 0x3c, spfs << 2);
	break;
	case CS42L73_VSP:
		snd_soc_component_update_bits(component, CS42L73_VXSPFS, 0xf0, spfs << 4);
	break;
	default:
	break;
	}
}