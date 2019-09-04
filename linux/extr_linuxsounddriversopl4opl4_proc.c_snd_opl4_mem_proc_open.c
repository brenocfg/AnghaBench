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
struct snd_opl4 {int /*<<< orphan*/  access_mutex; scalar_t__ memory_access; } ;
struct snd_info_entry {struct snd_opl4* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_opl4_mem_proc_open(struct snd_info_entry *entry,
				  unsigned short mode, void **file_private_data)
{
	struct snd_opl4 *opl4 = entry->private_data;

	mutex_lock(&opl4->access_mutex);
	if (opl4->memory_access) {
		mutex_unlock(&opl4->access_mutex);
		return -EBUSY;
	}
	opl4->memory_access++;
	mutex_unlock(&opl4->access_mutex);
	return 0;
}