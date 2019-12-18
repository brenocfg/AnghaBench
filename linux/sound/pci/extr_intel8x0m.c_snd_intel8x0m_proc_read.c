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
struct snd_info_entry {struct intel8x0m* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct intel8x0m {scalar_t__ device_type; } ;

/* Variables and functions */
 scalar_t__ DEVICE_ALI ; 
 int /*<<< orphan*/  GLOB_CNT ; 
 int /*<<< orphan*/  GLOB_STA ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_PCR ; 
 unsigned int ICH_SCR ; 
 unsigned int ICH_TCR ; 
 unsigned int igetdword (struct intel8x0m*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_intel8x0m_proc_read(struct snd_info_entry * entry,
				   struct snd_info_buffer *buffer)
{
	struct intel8x0m *chip = entry->private_data;
	unsigned int tmp;

	snd_iprintf(buffer, "Intel8x0m\n\n");
	if (chip->device_type == DEVICE_ALI)
		return;
	tmp = igetdword(chip, ICHREG(GLOB_STA));
	snd_iprintf(buffer, "Global control        : 0x%08x\n",
		    igetdword(chip, ICHREG(GLOB_CNT)));
	snd_iprintf(buffer, "Global status         : 0x%08x\n", tmp);
	snd_iprintf(buffer, "AC'97 codecs ready    :%s%s%s%s\n",
			tmp & ICH_PCR ? " primary" : "",
			tmp & ICH_SCR ? " secondary" : "",
			tmp & ICH_TCR ? " tertiary" : "",
			(tmp & (ICH_PCR | ICH_SCR | ICH_TCR)) == 0 ? " none" : "");
}