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
struct foo_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct foo_obj*) ; 
 struct foo_obj* to_foo_obj (struct kobject*) ; 

__attribute__((used)) static void foo_release(struct kobject *kobj)
{
	struct foo_obj *foo;

	foo = to_foo_obj(kobj);
	kfree(foo);
}