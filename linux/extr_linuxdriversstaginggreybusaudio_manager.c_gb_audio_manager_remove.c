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
struct gb_audio_manager_module {int /*<<< orphan*/  kobj; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct gb_audio_manager_module* gb_audio_manager_get_locked (int) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_id ; 
 int /*<<< orphan*/  modules_rwsem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gb_audio_manager_remove(int id)
{
	struct gb_audio_manager_module *module;

	down_write(&modules_rwsem);

	module = gb_audio_manager_get_locked(id);
	if (!module) {
		up_write(&modules_rwsem);
		return -EINVAL;
	}
	list_del(&module->list);
	kobject_put(&module->kobj);
	up_write(&modules_rwsem);
	ida_simple_remove(&module_id, id);
	return 0;
}