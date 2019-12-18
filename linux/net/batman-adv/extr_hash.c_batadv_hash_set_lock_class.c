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
typedef  size_t u32 ;
struct lock_class_key {int dummy; } ;
struct batadv_hashtable {size_t size; int /*<<< orphan*/ * list_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 

void batadv_hash_set_lock_class(struct batadv_hashtable *hash,
				struct lock_class_key *key)
{
	u32 i;

	for (i = 0; i < hash->size; i++)
		lockdep_set_class(&hash->list_locks[i], key);
}