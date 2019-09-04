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
struct xdp_uqueue {scalar_t__ cached_cons; scalar_t__ cached_prod; scalar_t__* consumer; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 xq_nb_free(struct xdp_uqueue *q, u32 ndescs)
{
	u32 free_entries = q->cached_cons - q->cached_prod;

	if (free_entries >= ndescs)
		return free_entries;

	/* Refresh the local tail pointer */
	q->cached_cons = *q->consumer + q->size;
	return q->cached_cons - q->cached_prod;
}