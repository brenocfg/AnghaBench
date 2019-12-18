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
struct xsk_ring_prod {size_t cached_prod; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 size_t xsk_prod_nb_free (struct xsk_ring_prod*,size_t) ; 

__attribute__((used)) static inline size_t xsk_ring_prod__reserve(struct xsk_ring_prod *prod,
					    size_t nb, __u32 *idx)
{
	if (xsk_prod_nb_free(prod, nb) < nb)
		return 0;

	*idx = prod->cached_prod;
	prod->cached_prod += nb;

	return nb;
}