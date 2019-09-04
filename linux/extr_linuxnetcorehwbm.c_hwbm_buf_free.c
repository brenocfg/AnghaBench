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
struct hwbm_pool {scalar_t__ frag_size; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 

void hwbm_buf_free(struct hwbm_pool *bm_pool, void *buf)
{
	if (likely(bm_pool->frag_size <= PAGE_SIZE))
		skb_free_frag(buf);
	else
		kfree(buf);
}