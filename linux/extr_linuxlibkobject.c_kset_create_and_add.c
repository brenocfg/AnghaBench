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
struct kset_uevent_ops {int dummy; } ;
struct kset {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kset*) ; 
 struct kset* kset_create (char const*,struct kset_uevent_ops const*,struct kobject*) ; 
 int kset_register (struct kset*) ; 

struct kset *kset_create_and_add(const char *name,
				 const struct kset_uevent_ops *uevent_ops,
				 struct kobject *parent_kobj)
{
	struct kset *kset;
	int error;

	kset = kset_create(name, uevent_ops, parent_kobj);
	if (!kset)
		return NULL;
	error = kset_register(kset);
	if (error) {
		kfree(kset);
		return NULL;
	}
	return kset;
}