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
struct snd_info_entry {struct lola* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct lola {int /*<<< orphan*/  debug_res_ex; int /*<<< orphan*/  debug_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lola_proc_codec_rw_read(struct snd_info_entry *entry,
				    struct snd_info_buffer *buffer)
{
	struct lola *chip = entry->private_data;
	snd_iprintf(buffer, "0x%x 0x%x\n", chip->debug_res, chip->debug_res_ex);
}