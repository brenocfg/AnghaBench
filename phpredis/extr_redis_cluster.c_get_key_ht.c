#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisCluster ;
struct TYPE_6__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  slot; int /*<<< orphan*/  key_free; } ;
typedef  TYPE_2__ clusterKeyValHT ;
typedef  int /*<<< orphan*/  HashTable ;
typedef  int /*<<< orphan*/  HashPosition ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_hash_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_key_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_get_current_data_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_key_ht(redisCluster *c, HashTable *ht, HashPosition *ptr,
                      clusterKeyValHT *kv)
{
    zval *z_key;

    if ((z_key = zend_hash_get_current_data_ex(ht, ptr)) == NULL) {
        // Shouldn't happen, but check anyway
        CLUSTER_THROW_EXCEPTION("Internal Zend HashTable error", 0);
        return -1;
    }

    // Always want to work with strings
    convert_to_string(z_key);

    kv->key = Z_STRVAL_P(z_key);
    kv->key_len = Z_STRLEN_P(z_key);
    kv->key_free = redis_key_prefix(c->flags, &(kv->key), &(kv->key_len));

    // Hash our key
    kv->slot = cluster_hash_key(kv->key, kv->key_len);

    // Success
    return 0;
}