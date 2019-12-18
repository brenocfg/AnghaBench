#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t cmd_slot; TYPE_3__* cmd_sock; TYPE_1__** master; } ;
typedef  TYPE_2__ redisCluster ;
struct TYPE_11__ {scalar_t__ readonly; } ;
struct TYPE_9__ {scalar_t__ slaves; } ;
typedef  TYPE_3__ RedisSock ;

/* Variables and functions */
 scalar_t__ CLUSTER_SEND_PAYLOAD (TYPE_3__*,char const*,size_t) ; 
 scalar_t__ cluster_send_readonly (TYPE_3__*) ; 
 TYPE_3__* cluster_slot_sock (TYPE_2__*,size_t,int) ; 
 int /*<<< orphan*/  efree (int*) ; 
 int* emalloc (int) ; 
 int /*<<< orphan*/  fyshuffle (int*,int) ; 
 scalar_t__ zend_hash_num_elements (scalar_t__) ; 

__attribute__((used)) static int cluster_dist_write(redisCluster *c, const char *cmd, size_t sz,
                              int nomaster)
{
    int i, count = 1, *nodes;
    RedisSock *redis_sock;

    /* Determine our overall node count */
    if (c->master[c->cmd_slot]->slaves) {
        count += zend_hash_num_elements(c->master[c->cmd_slot]->slaves);
    }

    /* Allocate memory for master + slaves or just slaves */
    nodes = emalloc(sizeof(int)*count);

    /* Populate our array with the master and each of it's slaves, then
     * randomize them, so we will pick from the master or some slave.  */
    for (i = 0; i < count; i++) nodes[i] = i;
    fyshuffle(nodes, count);

    /* Iterate through our nodes until we find one we can write to or fail */
    for (i = 0; i < count; i++) {
        /* Skip if this is the master node and we don't want to query that */
        if (nomaster && nodes[i] == 0)
           continue;

        /* Get the slave for this index */
        redis_sock = cluster_slot_sock(c, c->cmd_slot, nodes[i]);
        if (!redis_sock) continue;

        /* If we're not on the master, attempt to send the READONLY command to
         * this slave, and skip it if that fails */
        if (nodes[i] == 0 || redis_sock->readonly ||
            cluster_send_readonly(redis_sock) == 0)
        {
            /* Attempt to send the command */
            if (CLUSTER_SEND_PAYLOAD(redis_sock, cmd, sz)) {
                c->cmd_sock = redis_sock;
                efree(nodes);
                return 0;
            }
        }
    }

    /* Clean up our shuffled array */
    efree(nodes);

    /* Couldn't send to the master or any slave */
    return -1;
}