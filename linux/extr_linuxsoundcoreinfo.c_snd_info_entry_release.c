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
struct snd_info_entry {int /*<<< orphan*/  module; TYPE_2__ c; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct snd_info_private_data* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct snd_info_entry*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int O_ACCMODE ; 
 int /*<<< orphan*/  kfree (struct snd_info_private_data*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_info_entry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_info_entry_release(struct inode *inode, struct file *file)
{
	struct snd_info_private_data *data = file->private_data;
	struct snd_info_entry *entry = data->entry;

	if (entry->c.ops->release)
		entry->c.ops->release(entry, file->f_flags & O_ACCMODE,
				      data->file_private_data);
	module_put(entry->module);
	kfree(data);
	return 0;
}