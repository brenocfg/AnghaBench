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
struct snd_info_entry {struct snd_ali* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ali_proc_read(struct snd_info_entry *entry,
			      struct snd_info_buffer *buf)
{
	struct snd_ali *codec = entry->private_data;
	int i;
	for (i = 0; i < 256 ; i+= 4)
		snd_iprintf(buf, "%02x: %08x\n", i, inl(ALI_REG(codec, i)));
}