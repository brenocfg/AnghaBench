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
struct snd_info_entry {struct atiixp* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct atiixp {scalar_t__ remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_atiixp_proc_read(struct snd_info_entry *entry,
				 struct snd_info_buffer *buffer)
{
	struct atiixp *chip = entry->private_data;
	int i;

	for (i = 0; i < 256; i += 4)
		snd_iprintf(buffer, "%02x: %08x\n", i, readl(chip->remap_addr + i));
}