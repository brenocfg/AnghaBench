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
struct svc_xprt {int /*<<< orphan*/  xpt_nr_rqsts; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int svc_rpc_per_connection_limit ; 

__attribute__((used)) static bool svc_xprt_slots_in_range(struct svc_xprt *xprt)
{
	unsigned int limit = svc_rpc_per_connection_limit;
	int nrqsts = atomic_read(&xprt->xpt_nr_rqsts);

	return limit == 0 || (nrqsts >= 0 && nrqsts < limit);
}