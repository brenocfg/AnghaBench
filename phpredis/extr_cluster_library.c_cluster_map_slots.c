#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {short low; short high; } ;
typedef  TYPE_1__ redisSlotRange ;
struct TYPE_17__ {int /*<<< orphan*/  slots; } ;
typedef  TYPE_2__ redisClusterNode ;
struct TYPE_18__ {TYPE_2__** master; int /*<<< orphan*/  nodes; } ;
typedef  TYPE_3__ redisCluster ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_19__ {int elements; char* str; int len; scalar_t__ integer; struct TYPE_19__** element; } ;
typedef  TYPE_4__ clusterReply ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_SLOTS_INNER (TYPE_4__*) ; 
 int /*<<< orphan*/  VALIDATE_SLOTS_OUTER (TYPE_4__*) ; 
 int /*<<< orphan*/  cluster_node_add_slave (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* cluster_node_create (TYPE_3__*,char*,int,unsigned short,short,int) ; 
 int snprintf (char*,int,char*,char*,unsigned short) ; 
 TYPE_2__* zend_hash_str_find_ptr (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zend_hash_str_update_ptr (int /*<<< orphan*/ ,char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_llist_add_element (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int cluster_map_slots(redisCluster *c, clusterReply *r) {
    redisClusterNode *pnode, *master, *slave;
    redisSlotRange range;
    int i,j, hlen, klen;
    short low, high;
    clusterReply *r2, *r3;
    unsigned short port;
    char *host, key[1024];

    for (i = 0; i < r->elements; i++) {
        // Inner response
        r2 = r->element[i];

        // Validate outer and master slot
        if (!VALIDATE_SLOTS_OUTER(r2) || !VALIDATE_SLOTS_INNER(r2->element[2])) {
            return -1;
        }

        // Master
        r3 = r2->element[2];

        // Grab our slot range, as well as master host/port
        low  = (unsigned short)r2->element[0]->integer;
        high = (unsigned short)r2->element[1]->integer;
        host = r3->element[0]->str;
        hlen = r3->element[0]->len;
        port = (unsigned short)r3->element[1]->integer;

        // If the node is new, create and add to nodes.  Otherwise use it.
        klen = snprintf(key, sizeof(key), "%s:%d", host, port);
        if ((pnode = zend_hash_str_find_ptr(c->nodes, key, klen)) == NULL) {
            master = cluster_node_create(c, host, hlen, port, low, 0);
            zend_hash_str_update_ptr(c->nodes, key, klen, master);
        } else {
            master = pnode;
        }

        // Attach slaves
        for (j = 3; j< r2->elements; j++) {
            r3 = r2->element[j];
            if (!VALIDATE_SLOTS_INNER(r3)) {
                return -1;
            }

            // Skip slaves where the host is ""
            if (r3->element[0]->len == 0) continue;

            // Attach this node to our slave
            slave = cluster_node_create(c, r3->element[0]->str,
                (int)r3->element[0]->len,
                (unsigned short)r3->element[1]->integer, low, 1);
            cluster_node_add_slave(master, slave);
        }

        // Attach this node to each slot in the range
        for (j = low; j<= high; j++) {
            c->master[j] = master;
        }

        /* Append to our list of slot ranges */
        range.low = low; range.high = high;
        zend_llist_add_element(&master->slots, &range);
    }

    // Success
    return 0;
}