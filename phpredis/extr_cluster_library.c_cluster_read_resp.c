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
struct TYPE_3__ {int /*<<< orphan*/  reply_len; int /*<<< orphan*/ * line_reply; int /*<<< orphan*/  reply_type; int /*<<< orphan*/  cmd_sock; } ;
typedef  TYPE_1__ redisCluster ;
typedef  int /*<<< orphan*/  clusterReply ;

/* Variables and functions */
 int /*<<< orphan*/ * cluster_read_sock_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

clusterReply *cluster_read_resp(redisCluster *c, int status_strings) {
    return cluster_read_sock_resp(c->cmd_sock, c->reply_type,
                                  status_strings ? c->line_reply : NULL,
                                  c->reply_len);
}