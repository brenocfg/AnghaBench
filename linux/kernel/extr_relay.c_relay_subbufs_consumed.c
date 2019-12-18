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
struct rchan_buf {size_t subbufs_produced; size_t subbufs_consumed; } ;
struct rchan {size_t n_subbufs; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 unsigned int NR_CPUS ; 
 struct rchan_buf** per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

void relay_subbufs_consumed(struct rchan *chan,
			    unsigned int cpu,
			    size_t subbufs_consumed)
{
	struct rchan_buf *buf;

	if (!chan || cpu >= NR_CPUS)
		return;

	buf = *per_cpu_ptr(chan->buf, cpu);
	if (!buf || subbufs_consumed > chan->n_subbufs)
		return;

	if (subbufs_consumed > buf->subbufs_produced - buf->subbufs_consumed)
		buf->subbufs_consumed = buf->subbufs_produced;
	else
		buf->subbufs_consumed += subbufs_consumed;
}