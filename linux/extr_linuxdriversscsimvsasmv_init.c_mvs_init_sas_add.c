#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
struct mvs_info {TYPE_2__* phy; int /*<<< orphan*/  sas_addr; TYPE_1__* chip; } ;
struct TYPE_4__ {int dev_sas_addr; } ;
struct TYPE_3__ {size_t n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvs_init_sas_add(struct mvs_info *mvi)
{
	u8 i;
	for (i = 0; i < mvi->chip->n_phy; i++) {
		mvi->phy[i].dev_sas_addr = 0x5005043011ab0000ULL;
		mvi->phy[i].dev_sas_addr =
			cpu_to_be64((u64)(*(u64 *)&mvi->phy[i].dev_sas_addr));
	}

	memcpy(mvi->sas_addr, &mvi->phy[0].dev_sas_addr, SAS_ADDR_SIZE);
}