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
struct p9_req_t {int dummy; } ;
struct p9_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rdma_cancel(struct p9_client *client, struct p9_req_t *req)
{
	/* Nothing to do here.
	 * We will take care of it (if we have to) in rdma_cancelled()
	 */
	return 1;
}