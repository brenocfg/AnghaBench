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
struct efx_nic {unsigned int vi_stride; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int efx_paged_reg(struct efx_nic *efx, unsigned int page,
					 unsigned int reg)
{
	return page * efx->vi_stride + reg;
}