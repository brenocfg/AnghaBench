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
struct p9_trans_rdma {int /*<<< orphan*/  excess_rc; } ;
struct p9_req_t {int dummy; } ;
struct p9_client {struct p9_trans_rdma* trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rdma_cancelled(struct p9_client *client, struct p9_req_t *req)
{
	struct p9_trans_rdma *rdma = client->trans;
	atomic_inc(&rdma->excess_rc);
	return 0;
}