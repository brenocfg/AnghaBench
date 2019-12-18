#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double timeout; double read_timeout; int persistent; long waitms; int /*<<< orphan*/  nodes; int /*<<< orphan*/  auth; } ;
typedef  TYPE_1__ redisCluster ;
typedef  int /*<<< orphan*/  redisCachedCluster ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * cluster_cache_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_cache_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_init_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ cluster_init_seeds (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ cluster_map_keyspace (TYPE_1__*) ; 
 int /*<<< orphan*/  cluster_validate_args (double,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_init (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void redis_cluster_init(redisCluster *c, HashTable *ht_seeds, double timeout,
                               double read_timeout, int persistent, char *auth,
                               size_t auth_len)
{
    redisCachedCluster *cc;

    cluster_validate_args(timeout, read_timeout, ht_seeds);

    if (auth && auth_len > 0) {
        c->auth = zend_string_init(auth, auth_len, 0);
    }

    c->timeout = timeout;
    c->read_timeout = read_timeout;
    c->persistent = persistent;

    /* Calculate the number of miliseconds we will wait when bouncing around,
     * (e.g. a node goes down), which is not the same as a standard timeout. */
    c->waitms = (long)(timeout * 1000);

    /* Attempt to load from cache */
    if ((cc = cluster_cache_load(ht_seeds))) {
        cluster_init_cache(c, cc);
    } else if (cluster_init_seeds(c, ht_seeds) == SUCCESS &&
               cluster_map_keyspace(c) == SUCCESS)
    {
        cluster_cache_store(ht_seeds, c->nodes);
    }
}