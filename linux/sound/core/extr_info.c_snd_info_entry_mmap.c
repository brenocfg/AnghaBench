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
struct vm_area_struct {int dummy; } ;
struct snd_info_private_data {int /*<<< orphan*/  file_private_data; struct snd_info_entry* entry; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct snd_info_entry {TYPE_2__ c; } ;
struct inode {int dummy; } ;
struct file {struct snd_info_private_data* private_data; } ;
struct TYPE_3__ {int (* mmap ) (struct snd_info_entry*,int /*<<< orphan*/ ,struct inode*,struct file*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 struct inode* file_inode (struct file*) ; 
 int stub1 (struct snd_info_entry*,int /*<<< orphan*/ ,struct inode*,struct file*,struct vm_area_struct*) ; 

__attribute__((used)) static int snd_info_entry_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file_inode(file);
	struct snd_info_private_data *data;
	struct snd_info_entry *entry;

	data = file->private_data;
	if (data == NULL)
		return 0;
	entry = data->entry;
	if (!entry->c.ops->mmap)
		return -ENXIO;
	return entry->c.ops->mmap(entry, data->file_private_data,
				  inode, file, vma);
}