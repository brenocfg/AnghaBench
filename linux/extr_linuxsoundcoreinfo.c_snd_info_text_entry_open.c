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
struct snd_info_private_data {struct snd_info_private_data* rbuffer; } ;
struct snd_info_entry {int /*<<< orphan*/  module; scalar_t__ size; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_info_entry* PDE_DATA (struct inode*) ; 
 int alloc_info_private (struct snd_info_entry*,struct snd_info_private_data**) ; 
 int /*<<< orphan*/  info_mutex ; 
 int /*<<< orphan*/  kfree (struct snd_info_private_data*) ; 
 struct snd_info_private_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct snd_info_private_data*) ; 
 int single_open_size (struct file*,int /*<<< orphan*/ ,struct snd_info_private_data*,scalar_t__) ; 
 int /*<<< orphan*/  snd_info_seq_show ; 

__attribute__((used)) static int snd_info_text_entry_open(struct inode *inode, struct file *file)
{
	struct snd_info_entry *entry = PDE_DATA(inode);
	struct snd_info_private_data *data;
	int err;

	mutex_lock(&info_mutex);
	err = alloc_info_private(entry, &data);
	if (err < 0)
		goto unlock;

	data->rbuffer = kzalloc(sizeof(*data->rbuffer), GFP_KERNEL);
	if (!data->rbuffer) {
		err = -ENOMEM;
		goto error;
	}
	if (entry->size)
		err = single_open_size(file, snd_info_seq_show, data,
				       entry->size);
	else
		err = single_open(file, snd_info_seq_show, data);
	if (err < 0)
		goto error;
	mutex_unlock(&info_mutex);
	return 0;

 error:
	kfree(data->rbuffer);
	kfree(data);
	module_put(entry->module);
 unlock:
	mutex_unlock(&info_mutex);
	return err;
}