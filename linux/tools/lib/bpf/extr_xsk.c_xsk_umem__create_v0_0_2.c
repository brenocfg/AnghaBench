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
struct xsk_umem_config_v1 {int dummy; } ;
struct xsk_umem_config {scalar_t__ flags; } ;
struct xsk_umem {int dummy; } ;
struct xsk_ring_prod {int dummy; } ;
struct xsk_ring_cons {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct xsk_umem_config*,struct xsk_umem_config const*,int) ; 
 int xsk_umem__create_v0_0_4 (struct xsk_umem**,void*,int /*<<< orphan*/ ,struct xsk_ring_prod*,struct xsk_ring_cons*,struct xsk_umem_config*) ; 

int xsk_umem__create_v0_0_2(struct xsk_umem **umem_ptr, void *umem_area,
			    __u64 size, struct xsk_ring_prod *fill,
			    struct xsk_ring_cons *comp,
			    const struct xsk_umem_config *usr_config)
{
	struct xsk_umem_config config;

	memcpy(&config, usr_config, sizeof(struct xsk_umem_config_v1));
	config.flags = 0;

	return xsk_umem__create_v0_0_4(umem_ptr, umem_area, size, fill, comp,
					&config);
}