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
struct key_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_GC_REAPING_KEYTYPE ; 
 int /*<<< orphan*/  KEY_GC_REAP_KEYTYPE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  kdebug (char*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 struct key_type* key_gc_dead_keytype ; 
 int /*<<< orphan*/  key_gc_flags ; 
 int /*<<< orphan*/  key_gc_work ; 
 int /*<<< orphan*/  kleave (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void key_gc_keytype(struct key_type *ktype)
{
	kenter("%s", ktype->name);

	key_gc_dead_keytype = ktype;
	set_bit(KEY_GC_REAPING_KEYTYPE, &key_gc_flags);
	smp_mb();
	set_bit(KEY_GC_REAP_KEYTYPE, &key_gc_flags);

	kdebug("schedule");
	schedule_work(&key_gc_work);

	kdebug("sleep");
	wait_on_bit(&key_gc_flags, KEY_GC_REAPING_KEYTYPE,
		    TASK_UNINTERRUPTIBLE);

	key_gc_dead_keytype = NULL;
	kleave("");
}