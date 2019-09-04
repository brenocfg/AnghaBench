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
struct rpc_iostats {int /*<<< orphan*/  om_lock; } ;
struct rpc_clnt {int cl_maxproc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rpc_iostats* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct rpc_iostats *rpc_alloc_iostats(struct rpc_clnt *clnt)
{
	struct rpc_iostats *stats;
	int i;

	stats = kcalloc(clnt->cl_maxproc, sizeof(*stats), GFP_KERNEL);
	if (stats) {
		for (i = 0; i < clnt->cl_maxproc; i++)
			spin_lock_init(&stats[i].om_lock);
	}
	return stats;
}