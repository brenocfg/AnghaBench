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
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  efx_paged_reg (struct efx_nic*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  efx_writed (struct efx_nic*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
_efx_writed_page(struct efx_nic *efx, const efx_dword_t *value,
		 unsigned int reg, unsigned int page)
{
	efx_writed(efx, value, efx_paged_reg(efx, page, reg));
}