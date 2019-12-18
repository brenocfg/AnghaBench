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
struct xsk_ring_cons {size_t* consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  libbpf_smp_rwmb () ; 

__attribute__((used)) static inline void xsk_ring_cons__release(struct xsk_ring_cons *cons, size_t nb)
{
	/* Make sure data has been read before indicating we are done
	 * with the entries by updating the consumer pointer.
	 */
	libbpf_smp_rwmb();

	*cons->consumer += nb;
}