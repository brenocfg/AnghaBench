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
struct hdspm {scalar_t__ io_type; } ;

/* Variables and functions */
 scalar_t__ AES32 ; 
 int /*<<< orphan*/  ENUMERATED_CTL_INFO (struct snd_ctl_elem_info*,char const* const*) ; 
 scalar_t__ MADI ; 
 struct hdspm* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_hdspm_info_autosync_ref(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_info *uinfo)
{
	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	if (AES32 == hdspm->io_type) {
		static const char *const texts[] = { "WordClock", "AES1", "AES2", "AES3",
			"AES4",	"AES5", "AES6", "AES7", "AES8", "TCO", "Sync In", "None"};

		ENUMERATED_CTL_INFO(uinfo, texts);
	} else if (MADI == hdspm->io_type) {
		static const char *const texts[] = {"Word Clock", "MADI", "TCO",
			"Sync In", "None" };

		ENUMERATED_CTL_INFO(uinfo, texts);
	}
	return 0;
}