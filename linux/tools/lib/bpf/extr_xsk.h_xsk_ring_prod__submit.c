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
struct xsk_ring_prod {size_t* producer; } ;

/* Variables and functions */
 int /*<<< orphan*/  libbpf_smp_wmb () ; 

__attribute__((used)) static inline void xsk_ring_prod__submit(struct xsk_ring_prod *prod, size_t nb)
{
	/* Make sure everything has been written to the ring before indicating
	 * this to the kernel by writing the producer pointer.
	 */
	libbpf_smp_wmb();

	*prod->producer += nb;
}