#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  redisClusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  cluster_free_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ht_free_node(zval *data) {
    redisClusterNode *node = *(redisClusterNode**)data;
    cluster_free_node(node);
}