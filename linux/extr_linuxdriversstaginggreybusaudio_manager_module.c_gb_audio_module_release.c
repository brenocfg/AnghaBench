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
struct kobject {int dummy; } ;
struct gb_audio_manager_module {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gb_audio_manager_module*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct gb_audio_manager_module* to_gb_audio_module (struct kobject*) ; 

__attribute__((used)) static void gb_audio_module_release(struct kobject *kobj)
{
	struct gb_audio_manager_module *module = to_gb_audio_module(kobj);

	pr_info("Destroying audio module #%d\n", module->id);
	/* TODO -> delete from list */
	kfree(module);
}