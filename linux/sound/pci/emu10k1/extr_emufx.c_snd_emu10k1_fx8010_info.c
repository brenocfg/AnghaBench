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
struct snd_emu10k1_fx8010_info {int external_tram_size; int /*<<< orphan*/  gpr_controls; int /*<<< orphan*/ * extout_names; int /*<<< orphan*/ * extin_names; int /*<<< orphan*/ * fxbus_names; int /*<<< orphan*/  internal_tram_size; } ;
struct TYPE_3__ {int bytes; } ;
struct TYPE_4__ {unsigned short fxbus_mask; unsigned short extin_mask; unsigned short extout_mask; int /*<<< orphan*/  gpr_count; TYPE_1__ etram_pages; int /*<<< orphan*/  itram_size; } ;
struct snd_emu10k1 {TYPE_2__ fx8010; scalar_t__ audigy; } ;

/* Variables and functions */
 char** audigy_ins ; 
 char** audigy_outs ; 
 int /*<<< orphan*/  copy_string (int /*<<< orphan*/ ,char*,char*,int) ; 
 char** creative_ins ; 
 char** creative_outs ; 
 char** fxbuses ; 

__attribute__((used)) static void snd_emu10k1_fx8010_info(struct snd_emu10k1 *emu,
				   struct snd_emu10k1_fx8010_info *info)
{
	char **fxbus, **extin, **extout;
	unsigned short fxbus_mask, extin_mask, extout_mask;
	int res;

	info->internal_tram_size = emu->fx8010.itram_size;
	info->external_tram_size = emu->fx8010.etram_pages.bytes / 2;
	fxbus = fxbuses;
	extin = emu->audigy ? audigy_ins : creative_ins;
	extout = emu->audigy ? audigy_outs : creative_outs;
	fxbus_mask = emu->fx8010.fxbus_mask;
	extin_mask = emu->fx8010.extin_mask;
	extout_mask = emu->fx8010.extout_mask;
	for (res = 0; res < 16; res++, fxbus++, extin++, extout++) {
		copy_string(info->fxbus_names[res], fxbus_mask & (1 << res) ? *fxbus : NULL, "FXBUS", res);
		copy_string(info->extin_names[res], extin_mask & (1 << res) ? *extin : NULL, "Unused", res);
		copy_string(info->extout_names[res], extout_mask & (1 << res) ? *extout : NULL, "Unused", res);
	}
	for (res = 16; res < 32; res++, extout++)
		copy_string(info->extout_names[res], extout_mask & (1 << res) ? *extout : NULL, "Unused", res);
	info->gpr_controls = emu->fx8010.gpr_count;
}