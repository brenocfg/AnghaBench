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
struct batadv_hashtable {struct batadv_hashtable* table; struct batadv_hashtable* list_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct batadv_hashtable*) ; 

void batadv_hash_destroy(struct batadv_hashtable *hash)
{
	kfree(hash->list_locks);
	kfree(hash->table);
	kfree(hash);
}