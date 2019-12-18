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
struct rpc_rqst {unsigned long rq_timeout; unsigned long rq_majortimeo; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long xprt_request_timeout(const struct rpc_rqst *req)
{
	unsigned long timeout = jiffies + req->rq_timeout;

	if (time_before(timeout, req->rq_majortimeo))
		return timeout;
	return req->rq_majortimeo;
}