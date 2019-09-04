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
typedef  scalar_t__ u32 ;
struct xdp_uqueue {scalar_t__ cached_prod; scalar_t__ cached_cons; scalar_t__* producer; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 xq_nb_avail(struct xdp_uqueue *q, u32 ndescs)
{
	u32 entries = q->cached_prod - q->cached_cons;

	if (entries == 0) {
		q->cached_prod = *q->producer;
		entries = q->cached_prod - q->cached_cons;
	}

	return (entries > ndescs) ? ndescs : entries;
}