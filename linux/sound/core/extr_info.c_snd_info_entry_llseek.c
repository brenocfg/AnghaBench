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
struct snd_info_entry {scalar_t__ size; int /*<<< orphan*/  access; TYPE_2__ c; } ;
struct file {scalar_t__ f_pos; struct snd_info_private_data* private_data; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {scalar_t__ (* llseek ) (struct snd_info_entry*,int /*<<< orphan*/ ,struct file*,scalar_t__,int) ;} ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct snd_info_entry*,int /*<<< orphan*/ ,struct file*,scalar_t__,int) ; 

__attribute__((used)) static loff_t snd_info_entry_llseek(struct file *file, loff_t offset, int orig)
{
	struct snd_info_private_data *data;
	struct snd_info_entry *entry;
	loff_t ret = -EINVAL, size;

	data = file->private_data;
	entry = data->entry;
	mutex_lock(&entry->access);
	if (entry->c.ops->llseek) {
		offset = entry->c.ops->llseek(entry,
					      data->file_private_data,
					      file, offset, orig);
		goto out;
	}

	size = entry->size;
	switch (orig) {
	case SEEK_SET:
		break;
	case SEEK_CUR:
		offset += file->f_pos;
		break;
	case SEEK_END:
		if (!size)
			goto out;
		offset += size;
		break;
	default:
		goto out;
	}
	if (offset < 0)
		goto out;
	if (size && offset > size)
		offset = size;
	file->f_pos = offset;
	ret = offset;
 out:
	mutex_unlock(&entry->access);
	return ret;
}