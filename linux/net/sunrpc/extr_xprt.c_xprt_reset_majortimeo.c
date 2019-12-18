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
struct rpc_rqst {int /*<<< orphan*/  rq_majortimeo; } ;

/* Variables and functions */
 scalar_t__ xprt_calc_majortimeo (struct rpc_rqst*) ; 

__attribute__((used)) static void xprt_reset_majortimeo(struct rpc_rqst *req)
{
	req->rq_majortimeo += xprt_calc_majortimeo(req);
}