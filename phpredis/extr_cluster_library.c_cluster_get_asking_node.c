#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisClusterNode ;
struct TYPE_4__ {char* redir_host; int redir_port; int /*<<< orphan*/  redir_slot; int /*<<< orphan*/  redir_host_len; int /*<<< orphan*/  nodes; } ;
typedef  TYPE_1__ redisCluster ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/ * cluster_node_create (TYPE_1__*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static redisClusterNode *cluster_get_asking_node(redisCluster *c) {
    redisClusterNode *pNode;
    char key[1024];
    int key_len;

    /* Hashed by host:port */
    key_len = snprintf(key, sizeof(key), "%s:%u", c->redir_host, c->redir_port);

    /* See if we've already attached to it */
    if ((pNode = zend_hash_str_find_ptr(c->nodes, key, key_len)) != NULL) {
        return pNode;
    }

    /* This host:port is unknown to us, so add it */
    pNode = cluster_node_create(c, c->redir_host, c->redir_host_len,
        c->redir_port, c->redir_slot, 0);

    /* Return the node */
   return pNode;
}