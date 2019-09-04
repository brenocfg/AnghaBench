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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t hashmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_lock_hashpower ; 
 int /*<<< orphan*/ * item_locks ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void item_unlock(uint32_t hv) {
    mutex_unlock(&item_locks[hv & hashmask(item_lock_hashpower)]);
}