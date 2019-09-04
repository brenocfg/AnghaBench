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
struct TYPE_3__ {int subscribed_slot; double timeout; double read_timeout; int failover; int persistent; long waitms; int /*<<< orphan*/  nodes; int /*<<< orphan*/  seeds; int /*<<< orphan*/ * err; int /*<<< orphan*/ * auth; scalar_t__ clusterdown; void* flags; } ;
typedef  TYPE_1__ redisCluster ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ ) ; 
 void* ecalloc (int,int) ; 
 int /*<<< orphan*/  ht_free_node ; 
 int /*<<< orphan*/  ht_free_seed ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

redisCluster *cluster_create(double timeout, double read_timeout,
                                           int failover, int persistent)
{
    redisCluster *c;

    /* Actual our actual cluster structure */
    c = ecalloc(1, sizeof(redisCluster));

    /* Initialize flags and settings */
    c->flags = ecalloc(1, sizeof(RedisSock));
    c->subscribed_slot = -1;
    c->clusterdown = 0;
    c->timeout = timeout;
    c->read_timeout = read_timeout;
    c->failover = failover;
    c->persistent = persistent;
    c->auth = NULL;
    c->err = NULL;

    /* Set up our waitms based on timeout */
    c->waitms  = (long)(1000 * timeout);

    /* Allocate our seeds hash table */
    ALLOC_HASHTABLE(c->seeds);
    zend_hash_init(c->seeds, 0, NULL, ht_free_seed, 0);

    /* Allocate our nodes HashTable */
    ALLOC_HASHTABLE(c->nodes);
    zend_hash_init(c->nodes, 0, NULL, ht_free_node, 0);

    return c;
}