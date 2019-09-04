#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  seeds; scalar_t__ auth; int /*<<< orphan*/  persistent; int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_1__ redisCluster ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_7__ {int port; int /*<<< orphan*/  host; int /*<<< orphan*/  auth; } ;
typedef  TYPE_2__ RedisSock ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 char* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/ ** cluster_shuffle_seeds (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ **) ; 
 TYPE_2__* redis_sock_create (char*,int,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_str_update_ptr (int /*<<< orphan*/ ,char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_string_copy (scalar_t__) ; 

int
cluster_init_seeds(redisCluster *cluster, HashTable *ht_seeds) {
    RedisSock *redis_sock;
    char *str, *psep, key[1024];
    int key_len, count, i;
    zval **z_seeds, *z_seed;

    /* Get our seeds in a randomized array */
    z_seeds = cluster_shuffle_seeds(ht_seeds, &count);

    // Iterate our seeds array
    for (i = 0; i < count; i++) {
        if ((z_seed = z_seeds[i]) == NULL) continue;

        ZVAL_DEREF(z_seed);

        /* Has to be a string */
        if (Z_TYPE_P(z_seed) != IS_STRING) continue;

        // Grab a copy of the string
        str = Z_STRVAL_P(z_seed);

        /* Make sure we have a colon for host:port.  Search right to left in the
         * case of IPv6 */
        if ((psep = strrchr(str, ':')) == NULL)
            continue;

        // Allocate a structure for this seed
        redis_sock = redis_sock_create(str, psep-str,
            (unsigned short)atoi(psep+1), cluster->timeout,
            cluster->read_timeout, cluster->persistent, NULL, 0);

        // Set auth information if specified
        if (cluster->auth) {
            redis_sock->auth = zend_string_copy(cluster->auth);
        }

        // Index this seed by host/port
        key_len = snprintf(key, sizeof(key), "%s:%u", ZSTR_VAL(redis_sock->host),
            redis_sock->port);

        // Add to our seed HashTable
        zend_hash_str_update_ptr(cluster->seeds, key, key_len, redis_sock);
    }

    efree(z_seeds);

    // Success if at least one seed seems valid
    return zend_hash_num_elements(cluster->seeds) > 0 ? SUCCESS : FAILURE;
}