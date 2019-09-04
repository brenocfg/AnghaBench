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
struct snd_info_entry {int dummy; } ;
struct hdspm {int io_type; int /*<<< orphan*/  card; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_hdspm_proc_ports_in ; 
 int /*<<< orphan*/  snd_hdspm_proc_ports_out ; 
 int /*<<< orphan*/  snd_hdspm_proc_read_aes32 ; 
 int /*<<< orphan*/  snd_hdspm_proc_read_madi ; 
 int /*<<< orphan*/  snd_hdspm_proc_read_raydat ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_hdspm_proc_init(struct hdspm *hdspm)
{
	struct snd_info_entry *entry;

	if (!snd_card_proc_new(hdspm->card, "hdspm", &entry)) {
		switch (hdspm->io_type) {
		case AES32:
			snd_info_set_text_ops(entry, hdspm,
					snd_hdspm_proc_read_aes32);
			break;
		case MADI:
			snd_info_set_text_ops(entry, hdspm,
					snd_hdspm_proc_read_madi);
			break;
		case MADIface:
			/* snd_info_set_text_ops(entry, hdspm,
			 snd_hdspm_proc_read_madiface); */
			break;
		case RayDAT:
			snd_info_set_text_ops(entry, hdspm,
					snd_hdspm_proc_read_raydat);
			break;
		case AIO:
			break;
		}
	}

	if (!snd_card_proc_new(hdspm->card, "ports.in", &entry)) {
		snd_info_set_text_ops(entry, hdspm, snd_hdspm_proc_ports_in);
	}

	if (!snd_card_proc_new(hdspm->card, "ports.out", &entry)) {
		snd_info_set_text_ops(entry, hdspm, snd_hdspm_proc_ports_out);
	}

#ifdef CONFIG_SND_DEBUG
	/* debug file to read all hdspm registers */
	if (!snd_card_proc_new(hdspm->card, "debug", &entry))
		snd_info_set_text_ops(entry, hdspm,
				snd_hdspm_proc_read_debug);
#endif
}