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
struct snd_info_entry {struct snd_ice1712* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_binary (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpld (struct snd_ice1712*) ; 
 int /*<<< orphan*/  get_mcr (struct snd_ice1712*) ; 
 int /*<<< orphan*/  get_scr (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_regs_read(struct snd_info_entry *entry,
		struct snd_info_buffer *buffer)
{
	struct snd_ice1712 *ice = entry->private_data;
	char bin_buffer[36];

	snd_iprintf(buffer, "SCR:	%s\n", get_binary(bin_buffer,
				get_scr(ice)));
	snd_iprintf(buffer, "MCR:	%s\n", get_binary(bin_buffer,
				get_mcr(ice)));
	snd_iprintf(buffer, "CPLD:	%s\n", get_binary(bin_buffer,
				get_cpld(ice)));
}