#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_wss {int hardware; TYPE_1__* card; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WSS_HW_INTERWAVE 130 
#define  WSS_HW_OPL3SA2 129 
#define  WSS_HW_OPTI93X 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 
 struct snd_wss* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_wss_info_mux(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts[4] = {
		"Line", "Aux", "Mic", "Mix"
	};
	static const char * const opl3sa_texts[4] = {
		"Line", "CD", "Mic", "Mix"
	};
	static const char * const gusmax_texts[4] = {
		"Line", "Synth", "Mic", "Mix"
	};
	const char * const *ptexts = texts;
	struct snd_wss *chip = snd_kcontrol_chip(kcontrol);

	if (snd_BUG_ON(!chip->card))
		return -EINVAL;
	if (!strcmp(chip->card->driver, "GUS MAX"))
		ptexts = gusmax_texts;
	switch (chip->hardware) {
	case WSS_HW_INTERWAVE:
		ptexts = gusmax_texts;
		break;
	case WSS_HW_OPTI93X:
	case WSS_HW_OPL3SA2:
		ptexts = opl3sa_texts;
		break;
	}
	return snd_ctl_enum_info(uinfo, 2, 4, ptexts);
}