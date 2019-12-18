#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  slots; struct TYPE_5__* slaves; } ;
typedef  TYPE_1__ redisClusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  redis_free_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_llist_destroy (int /*<<< orphan*/ *) ; 

void cluster_free_node(redisClusterNode *node) {
    if (node->slaves) {
        zend_hash_destroy(node->slaves);
        efree(node->slaves);
    }

    zend_llist_destroy(&node->slots);
    redis_free_socket(node->sock);

    efree(node);
}