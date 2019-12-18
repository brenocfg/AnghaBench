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
struct snd_info_entry {int* name; struct loopback* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct loopback {int /*<<< orphan*/  cable_lock; } ;

/* Variables and functions */
 int MAX_PCM_SUBSTREAMS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_substream_info (struct snd_info_buffer*,struct loopback*,int,int) ; 
 int strlen (int*) ; 

__attribute__((used)) static void print_cable_info(struct snd_info_entry *entry,
			     struct snd_info_buffer *buffer)
{
	struct loopback *loopback = entry->private_data;
	int sub, num;

	mutex_lock(&loopback->cable_lock);
	num = entry->name[strlen(entry->name)-1];
	num = num == '0' ? 0 : 1;
	for (sub = 0; sub < MAX_PCM_SUBSTREAMS; sub++)
		print_substream_info(buffer, loopback, sub, num);
	mutex_unlock(&loopback->cable_lock);
}