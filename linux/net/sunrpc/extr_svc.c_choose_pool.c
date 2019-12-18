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
struct svc_serv {size_t sv_nrpools; struct svc_pool* sv_pools; } ;
struct svc_pool {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct svc_pool *
choose_pool(struct svc_serv *serv, struct svc_pool *pool, unsigned int *state)
{
	if (pool != NULL)
		return pool;

	return &serv->sv_pools[(*state)++ % serv->sv_nrpools];
}