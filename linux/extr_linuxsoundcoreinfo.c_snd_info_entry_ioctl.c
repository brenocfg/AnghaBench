#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_info_private_data {int /*<<< orphan*/  file_private_data; struct snd_info_entry* entry; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct snd_info_entry {TYPE_2__ c; } ;
struct file {struct snd_info_private_data* private_data; } ;
struct TYPE_3__ {long (* ioctl ) (struct snd_info_entry*,int /*<<< orphan*/ ,struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long ENOTTY ; 
 long stub1 (struct snd_info_entry*,int /*<<< orphan*/ ,struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long snd_info_entry_ioctl(struct file *file, unsigned int cmd,
				unsigned long arg)
{
	struct snd_info_private_data *data = file->private_data;
	struct snd_info_entry *entry = data->entry;

	if (!entry->c.ops->ioctl)
		return -ENOTTY;
	return entry->c.ops->ioctl(entry, data->file_private_data,
				   file, cmd, arg);
}