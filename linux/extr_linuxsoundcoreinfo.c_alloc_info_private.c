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
struct snd_info_private_data {struct snd_info_entry* entry; } ;
struct snd_info_entry {int /*<<< orphan*/  module; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_info_private_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_info_private(struct snd_info_entry *entry,
			      struct snd_info_private_data **ret)
{
	struct snd_info_private_data *data;

	if (!entry || !entry->p)
		return -ENODEV;
	if (!try_module_get(entry->module))
		return -EFAULT;
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		module_put(entry->module);
		return -ENOMEM;
	}
	data->entry = entry;
	*ret = data;
	return 0;
}