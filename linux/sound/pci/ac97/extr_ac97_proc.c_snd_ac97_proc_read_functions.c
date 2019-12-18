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
struct snd_info_buffer {int dummy; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_FUNC_INFO ; 
 int /*<<< orphan*/  AC97_FUNC_SELECT ; 
 int /*<<< orphan*/  AC97_SENSE_INFO ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_ac97_proc_read_functions(struct snd_ac97 *ac97, struct snd_info_buffer *buffer)
{
	int header = 0, function;
	unsigned short info, sense_info;
	static const char *function_names[12] = {
		"Master Out", "AUX Out", "Center/LFE Out", "SPDIF Out",
		"Phone In", "Mic 1", "Mic 2", "Line In", "CD In", "Video In",
		"Aux In", "Mono Out"
	};
	static const char *locations[8] = {
		"Rear I/O Panel", "Front Panel", "Motherboard", "Dock/External",
		"reserved", "reserved", "reserved", "NC/unused"
	};

	for (function = 0; function < 12; ++function) {
		snd_ac97_write(ac97, AC97_FUNC_SELECT, function << 1);
		info = snd_ac97_read(ac97, AC97_FUNC_INFO);
		if (!(info & 0x0001))
			continue;
		if (!header) {
			snd_iprintf(buffer, "\n                    Gain     Inverted  Buffer delay  Location\n");
			header = 1;
		}
		sense_info = snd_ac97_read(ac97, AC97_SENSE_INFO);
		snd_iprintf(buffer, "%-17s: %3d.%d dBV    %c      %2d/fs         %s\n",
			    function_names[function],
			    (info & 0x8000 ? -1 : 1) * ((info & 0x7000) >> 12) * 3 / 2,
			    ((info & 0x0800) >> 11) * 5,
			    info & 0x0400 ? 'X' : '-',
			    (info & 0x03e0) >> 5,
			    locations[sense_info >> 13]);
	}
}