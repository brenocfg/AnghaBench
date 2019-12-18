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
struct svc_serv {unsigned int sv_nrpools; void* sv_pools; } ;
struct seq_file {struct svc_serv* private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 

__attribute__((used)) static void *svc_pool_stats_start(struct seq_file *m, loff_t *pos)
{
	unsigned int pidx = (unsigned int)*pos;
	struct svc_serv *serv = m->private;

	dprintk("svc_pool_stats_start, *pidx=%u\n", pidx);

	if (!pidx)
		return SEQ_START_TOKEN;
	return (pidx > serv->sv_nrpools ? NULL : &serv->sv_pools[pidx-1]);
}