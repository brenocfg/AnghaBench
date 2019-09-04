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
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_info_get_line (struct snd_info_buffer*,char*,int) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned int,unsigned int) ; 

__attribute__((used)) static void wm_proc_regs_write(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct snd_ice1712 *ice = entry->private_data;
	char line[64];
	unsigned int reg, val;
	mutex_lock(&ice->gpio_mutex);
	while (!snd_info_get_line(buffer, line, sizeof(line))) {
		if (sscanf(line, "%x %x", &reg, &val) != 2)
			continue;
		if (reg <= 0x17 && val <= 0xffff)
			wm_put(ice, reg, val);
	}
	mutex_unlock(&ice->gpio_mutex);
}