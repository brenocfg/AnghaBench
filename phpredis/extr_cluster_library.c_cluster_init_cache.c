#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  redisClusterNode ;
struct TYPE_15__ {int /*<<< orphan*/ ** master; int /*<<< orphan*/  nodes; int /*<<< orphan*/  seeds; int /*<<< orphan*/  persistent; int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  cache_key; } ;
typedef  TYPE_4__ redisCluster ;
struct TYPE_12__ {int port; int /*<<< orphan*/ * addr; } ;
struct TYPE_16__ {size_t slaves; size_t slots; TYPE_3__* slot; TYPE_2__* slave; TYPE_1__ host; } ;
typedef  TYPE_5__ redisCachedMaster ;
struct TYPE_17__ {int count; TYPE_5__* master; int /*<<< orphan*/  hash; } ;
typedef  TYPE_6__ redisCachedCluster ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_14__ {size_t low; size_t high; } ;
struct TYPE_13__ {int /*<<< orphan*/  port; int /*<<< orphan*/ * addr; } ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int HOST_NAME_MAX ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cached_master_clone (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  cluster_node_add_slave (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cluster_node_create (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  efree (int*) ; 
 int* emalloc (int) ; 
 int /*<<< orphan*/  fyshuffle (int*,size_t) ; 
 int /*<<< orphan*/ * redis_sock_create (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  zend_hash_str_update_ptr (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 

void cluster_init_cache(redisCluster *c, redisCachedCluster *cc) {
    RedisSock *sock;
    redisClusterNode *mnode, *slave;
    redisCachedMaster *cm;
    char key[HOST_NAME_MAX];
    size_t keylen, i, j, s;
    int *map;

    /* Randomize seeds */
    map = emalloc(sizeof(*map) * cc->count);
    for (i = 0; i < cc->count; i++) map[i] = i;
    fyshuffle(map, cc->count);

    /* Iterate over masters */
    for (i = 0; i < cc->count; i++) {
        /* Attach cache key */
        c->cache_key = cc->hash;

        /* Grab the next master */
        cm = &cc->master[map[i]];

        /* Hash our host and port */
        keylen = snprintf(key, sizeof(key), "%s:%u", ZSTR_VAL(cm->host.addr),
                          cm->host.port);

        /* Create socket */
        sock = redis_sock_create(ZSTR_VAL(cm->host.addr), ZSTR_LEN(cm->host.addr), cm->host.port,
                                 c->timeout, c->read_timeout, c->persistent,
                                 NULL, 0);

        /* Add to seed nodes */
        zend_hash_str_update_ptr(c->seeds, key, keylen, sock);

        /* Create master node */
        mnode = cached_master_clone(c, cm);

        /* Add our master */
        zend_hash_str_update_ptr(c->nodes, key, keylen, mnode);

        /* Attach any slaves */
        for (s = 0; s < cm->slaves; s++) {
            zend_string *host = cm->slave[s].addr;
            slave = cluster_node_create(c, ZSTR_VAL(host), ZSTR_LEN(host), cm->slave[s].port, 0, 1);
            cluster_node_add_slave(mnode, slave);
        }

        /* Hook up direct slot access */
        for (j = 0; j < cm->slots; j++) {
            for (s = cm->slot[j].low; s <= cm->slot[j].high; s++) {
                c->master[s] = mnode;
            }
        }
    }

    efree(map);
}