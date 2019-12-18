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
struct hdspm {int io_type; int /*<<< orphan*/  card; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct hdspm*,void (*) (struct snd_info_entry*,struct snd_info_buffer*)) ; 
 void snd_hdspm_proc_ports_in (struct snd_info_entry*,struct snd_info_buffer*) ; 
 void snd_hdspm_proc_ports_out (struct snd_info_entry*,struct snd_info_buffer*) ; 
 void snd_hdspm_proc_read_aes32 (struct snd_info_entry*,struct snd_info_buffer*) ; 
 void snd_hdspm_proc_read_debug (struct snd_info_entry*,struct snd_info_buffer*) ; 
 void snd_hdspm_proc_read_madi (struct snd_info_entry*,struct snd_info_buffer*) ; 
 void snd_hdspm_proc_read_raydat (struct snd_info_entry*,struct snd_info_buffer*) ; 

__attribute__((used)) static void snd_hdspm_proc_init(struct hdspm *hdspm)
{
	void (*read)(struct snd_info_entry *, struct snd_info_buffer *) = NULL;

	switch (hdspm->io_type) {
	case AES32:
		read = snd_hdspm_proc_read_aes32;
		break;
	case MADI:
		read = snd_hdspm_proc_read_madi;
		break;
	case MADIface:
		/* read = snd_hdspm_proc_read_madiface; */
		break;
	case RayDAT:
		read = snd_hdspm_proc_read_raydat;
		break;
	case AIO:
		break;
	}

	snd_card_ro_proc_new(hdspm->card, "hdspm", hdspm, read);
	snd_card_ro_proc_new(hdspm->card, "ports.in", hdspm,
			     snd_hdspm_proc_ports_in);
	snd_card_ro_proc_new(hdspm->card, "ports.out", hdspm,
			     snd_hdspm_proc_ports_out);

#ifdef CONFIG_SND_DEBUG
	/* debug file to read all hdspm registers */
	snd_card_ro_proc_new(hdspm->card, "debug", hdspm,
			     snd_hdspm_proc_read_debug);
#endif
}