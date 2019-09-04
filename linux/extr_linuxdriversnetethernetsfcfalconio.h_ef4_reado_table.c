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
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void ef4_reado_table(struct ef4_nic *efx, ef4_oword_t *value,
				     unsigned int reg, unsigned int index)
{
	ef4_reado(efx, value, reg + index * sizeof(ef4_oword_t));
}