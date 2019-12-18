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
struct snd_info_private_data {struct snd_info_private_data* wbuffer; int /*<<< orphan*/  buffer; struct snd_info_private_data* rbuffer; struct snd_info_entry* entry; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (struct snd_info_entry*,struct snd_info_private_data*) ;} ;
struct TYPE_4__ {TYPE_1__ text; } ;
struct snd_info_entry {int /*<<< orphan*/  module; TYPE_2__ c; } ;
struct seq_file {struct snd_info_private_data* private; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_info_private_data*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  stub1 (struct snd_info_entry*,struct snd_info_private_data*) ; 

__attribute__((used)) static int snd_info_text_entry_release(struct inode *inode, struct file *file)
{
	struct seq_file *m = file->private_data;
	struct snd_info_private_data *data = m->private;
	struct snd_info_entry *entry = data->entry;

	if (data->wbuffer && entry->c.text.write)
		entry->c.text.write(entry, data->wbuffer);

	single_release(inode, file);
	kfree(data->rbuffer);
	if (data->wbuffer) {
		kvfree(data->wbuffer->buffer);
		kfree(data->wbuffer);
	}

	module_put(entry->module);
	kfree(data);
	return 0;
}