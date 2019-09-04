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
struct key_type {int /*<<< orphan*/  name; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_gc_keytype (struct key_type*) ; 
 int /*<<< orphan*/  key_types_sem ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void unregister_key_type(struct key_type *ktype)
{
	down_write(&key_types_sem);
	list_del_init(&ktype->link);
	downgrade_write(&key_types_sem);
	key_gc_keytype(ktype);
	pr_notice("Key type %s unregistered\n", ktype->name);
	up_read(&key_types_sem);
}