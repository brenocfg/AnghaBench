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
struct TYPE_3__ {TYPE_2__* memhdr; scalar_t__ entries; } ;
struct snd_trident {int device; char* spurious_irq_count; char* spurious_irq_max_delta; int spdif_ctrl; int ac97_ctrl; TYPE_1__ tlb; } ;
struct snd_info_entry {struct snd_trident* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_4__ {char* size; char* used; } ;

/* Variables and functions */
#define  TRIDENT_DEVICE_ID_DX 130 
#define  TRIDENT_DEVICE_ID_NX 129 
#define  TRIDENT_DEVICE_ID_SI7018 128 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 char* snd_util_mem_avail (TYPE_2__*) ; 

__attribute__((used)) static void snd_trident_proc_read(struct snd_info_entry *entry, 
				  struct snd_info_buffer *buffer)
{
	struct snd_trident *trident = entry->private_data;
	char *s;

	switch (trident->device) {
	case TRIDENT_DEVICE_ID_SI7018:
		s = "SiS 7018 Audio";
		break;
	case TRIDENT_DEVICE_ID_DX:
		s = "Trident 4DWave PCI DX";
		break;
	case TRIDENT_DEVICE_ID_NX:
		s = "Trident 4DWave PCI NX";
		break;
	default:
		s = "???";
	}
	snd_iprintf(buffer, "%s\n\n", s);
	snd_iprintf(buffer, "Spurious IRQs    : %d\n", trident->spurious_irq_count);
	snd_iprintf(buffer, "Spurious IRQ dlta: %d\n", trident->spurious_irq_max_delta);
	if (trident->device == TRIDENT_DEVICE_ID_NX || trident->device == TRIDENT_DEVICE_ID_SI7018)
		snd_iprintf(buffer, "IEC958 Mixer Out : %s\n", trident->spdif_ctrl == 0x28 ? "on" : "off");
	if (trident->device == TRIDENT_DEVICE_ID_NX) {
		snd_iprintf(buffer, "Rear Speakers    : %s\n", trident->ac97_ctrl & 0x00000010 ? "on" : "off");
		if (trident->tlb.entries) {
			snd_iprintf(buffer,"\nVirtual Memory\n");
			snd_iprintf(buffer, "Memory Maximum : %d\n", trident->tlb.memhdr->size);
			snd_iprintf(buffer, "Memory Used    : %d\n", trident->tlb.memhdr->used);
			snd_iprintf(buffer, "Memory Free    : %d\n", snd_util_mem_avail(trident->tlb.memhdr));
		}
	}
}