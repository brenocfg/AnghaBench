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
struct TYPE_2__ {void* slot; } ;

/* Variables and functions */
 size_t CARD_SLOTA ; 
 size_t CARD_SLOTB ; 
 int /*<<< orphan*/  SLOTB_IS_CF ; 
 int /*<<< orphan*/  SLOTB_IS_FLASHROM ; 
 int /*<<< orphan*/  SLOTB_IS_NONE ; 
 int /*<<< orphan*/  SLOTB_IS_PCCARD ; 
 void* SLOT_NOPROBE_ALL ; 
 void* SLOT_NOPROBE_IO ; 
 void* SLOT_NOPROBE_MEM ; 
 int nr_irqs ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int vrc4171_irq ; 
 int /*<<< orphan*/  vrc4171_slotb ; 
 TYPE_1__* vrc4171_sockets ; 

__attribute__((used)) static int vrc4171_card_setup(char *options)
{
	if (options == NULL || *options == '\0')
		return 1;

	if (strncmp(options, "irq:", 4) == 0) {
		int irq;
		options += 4;
		irq = simple_strtoul(options, &options, 0);
		if (irq >= 0 && irq < nr_irqs)
			vrc4171_irq = irq;

		if (*options != ',')
			return 1;
		options++;
	}

	if (strncmp(options, "slota:", 6) == 0) {
		options += 6;
		if (*options != '\0') {
			if (strncmp(options, "memnoprobe", 10) == 0) {
				vrc4171_sockets[CARD_SLOTA].slot = SLOT_NOPROBE_MEM;
				options += 10;
			} else if (strncmp(options, "ionoprobe", 9) == 0) {
				vrc4171_sockets[CARD_SLOTA].slot = SLOT_NOPROBE_IO;
				options += 9;
			} else if ( strncmp(options, "noprobe", 7) == 0) {
				vrc4171_sockets[CARD_SLOTA].slot = SLOT_NOPROBE_ALL;
				options += 7;
			}

			if (*options != ',')
				return 1;
			options++;
		} else
			return 1;

	}

	if (strncmp(options, "slotb:", 6) == 0) {
		options += 6;
		if (*options != '\0') {
			if (strncmp(options, "pccard", 6) == 0) {
				vrc4171_slotb = SLOTB_IS_PCCARD;
				options += 6;
			} else if (strncmp(options, "cf", 2) == 0) {
				vrc4171_slotb = SLOTB_IS_CF;
				options += 2;
			} else if (strncmp(options, "flashrom", 8) == 0) {
				vrc4171_slotb = SLOTB_IS_FLASHROM;
				options += 8;
			} else if (strncmp(options, "none", 4) == 0) {
				vrc4171_slotb = SLOTB_IS_NONE;
				options += 4;
			}

			if (*options != ',')
				return 1;
			options++;

			if (strncmp(options, "memnoprobe", 10) == 0)
				vrc4171_sockets[CARD_SLOTB].slot = SLOT_NOPROBE_MEM;
			if (strncmp(options, "ionoprobe", 9) == 0)
				vrc4171_sockets[CARD_SLOTB].slot = SLOT_NOPROBE_IO;
			if (strncmp(options, "noprobe", 7) == 0)
				vrc4171_sockets[CARD_SLOTB].slot = SLOT_NOPROBE_ALL;
		}
	}

	return 1;
}