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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  lola_codec_read (struct lola*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_info_get_line (struct snd_info_buffer*,char*,int) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void lola_proc_codec_rw_write(struct snd_info_entry *entry,
				     struct snd_info_buffer *buffer)
{
	struct lola *chip = entry->private_data;
	char line[64];
	unsigned int id, verb, data, extdata;
	while (!snd_info_get_line(buffer, line, sizeof(line))) {
		if (sscanf(line, "%u %u %u %u", &id, &verb, &data, &extdata) != 4)
			continue;
		lola_codec_read(chip, id, verb, data, extdata,
				&chip->debug_res,
				&chip->debug_res_ex);
	}
}