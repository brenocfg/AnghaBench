#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisSlotRange ;
struct TYPE_7__ {unsigned short slot; short slave; TYPE_3__* sock; int /*<<< orphan*/  slots; int /*<<< orphan*/ * slaves; } ;
typedef  TYPE_1__ redisClusterNode ;
struct TYPE_8__ {scalar_t__ auth; int /*<<< orphan*/  persistent; int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ redisCluster ;
struct TYPE_9__ {int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 TYPE_1__* emalloc (int) ; 
 TYPE_3__* redis_sock_create (char*,size_t,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_llist_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_copy (scalar_t__) ; 

__attribute__((used)) static redisClusterNode*
cluster_node_create(redisCluster *c, char *host, size_t host_len,
                    unsigned short port, unsigned short slot, short slave)
{
    redisClusterNode *node = emalloc(sizeof(redisClusterNode));

    // It lives in at least this slot, flag slave status
    node->slot   = slot;
    node->slave  = slave;
    node->slaves = NULL;

    /* Initialize our list of slot ranges */
    zend_llist_init(&node->slots, sizeof(redisSlotRange), NULL, 0);

    // Attach socket
    node->sock = redis_sock_create(host, host_len, port, c->timeout,
        c->read_timeout, c->persistent, NULL, 0);

    if (c->auth) {
        node->sock->auth = zend_string_copy(c->auth);
    }

    return node;
}