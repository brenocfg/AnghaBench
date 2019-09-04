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
typedef  int /*<<< orphan*/  u16 ;
struct snd_pdacf {int dummy; } ;
struct snd_info_entry {struct snd_pdacf* private_data; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDAUDIOCF_FPGAREV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDAUDIOCF_REG_SCR ; 
 int /*<<< orphan*/  pdacf_reg_read (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void pdacf_proc_read(struct snd_info_entry * entry,
                            struct snd_info_buffer *buffer)
{
	struct snd_pdacf *chip = entry->private_data;
	u16 tmp;

	snd_iprintf(buffer, "PDAudioCF\n\n");
	tmp = pdacf_reg_read(chip, PDAUDIOCF_REG_SCR);
	snd_iprintf(buffer, "FPGA revision      : 0x%x\n", PDAUDIOCF_FPGAREV(tmp));
	                                   
}