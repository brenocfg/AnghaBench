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
typedef  int /*<<< orphan*/  u32 ;
struct batadv_hashtable {struct batadv_hashtable* table; int /*<<< orphan*/  size; void* list_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  batadv_hash_init (struct batadv_hashtable*) ; 
 int /*<<< orphan*/  kfree (struct batadv_hashtable*) ; 
 struct batadv_hashtable* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct batadv_hashtable *batadv_hash_new(u32 size)
{
	struct batadv_hashtable *hash;

	hash = kmalloc(sizeof(*hash), GFP_ATOMIC);
	if (!hash)
		return NULL;

	hash->table = kmalloc_array(size, sizeof(*hash->table), GFP_ATOMIC);
	if (!hash->table)
		goto free_hash;

	hash->list_locks = kmalloc_array(size, sizeof(*hash->list_locks),
					 GFP_ATOMIC);
	if (!hash->list_locks)
		goto free_table;

	hash->size = size;
	batadv_hash_init(hash);
	return hash;

free_table:
	kfree(hash->table);
free_hash:
	kfree(hash);
	return NULL;
}