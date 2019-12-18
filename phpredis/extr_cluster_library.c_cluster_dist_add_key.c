#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
struct TYPE_3__ {int /*<<< orphan*/ ** master; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisCluster ;
typedef  int /*<<< orphan*/  clusterKeyVal ;
typedef  int /*<<< orphan*/  clusterDistList ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/ * cluster_dl_add_key (int /*<<< orphan*/ *,char*,size_t,int) ; 
 int /*<<< orphan*/ * cluster_dl_create () ; 
 short cluster_hash_key (char*,size_t) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int redis_key_prefix (int /*<<< orphan*/ ,char**,size_t*) ; 
 int /*<<< orphan*/ * zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_index_update_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cluster_dist_add_key(redisCluster *c, HashTable *ht, char *key,
                          size_t key_len, clusterKeyVal **kv)
{
    int key_free;
    short slot;
    clusterDistList *dl;
    clusterKeyVal *retptr;

    // Prefix our key and hash it
    key_free = redis_key_prefix(c->flags, &key, &key_len);
    slot = cluster_hash_key(key, key_len);

    // We can't do this if we don't fully understand the keyspace
    if (c->master[slot] == NULL) {
        if (key_free) efree(key);
        return FAILURE;
    }

    // Look for this slot
    if ((dl = zend_hash_index_find_ptr(ht, (zend_ulong)slot)) == NULL) {
        dl = cluster_dl_create();
        zend_hash_index_update_ptr(ht, (zend_ulong)slot, dl);
    }

    // Now actually add this key
    retptr = cluster_dl_add_key(dl, key, key_len, key_free);

    // Push our return pointer if requested
    if (kv) *kv = retptr;

    return SUCCESS;
}