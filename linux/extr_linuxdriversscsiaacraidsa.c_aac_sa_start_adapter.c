#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  host_elapsed_seconds; } ;
union aac_init {TYPE_1__ r7; } ;
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  u32 ;
struct aac_dev {scalar_t__ init_pa; union aac_init* init; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_STRUCT_BASE_ADDRESS ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  sa_sync_cmd (struct aac_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aac_sa_start_adapter(struct aac_dev *dev)
{
	union aac_init *init;
	/*
	 * Fill in the remaining pieces of the init.
	 */
	init = dev->init;
	init->r7.host_elapsed_seconds = cpu_to_le32(ktime_get_real_seconds());
	/* We can only use a 32 bit address here */
	sa_sync_cmd(dev, INIT_STRUCT_BASE_ADDRESS, 
			(u32)(ulong)dev->init_pa, 0, 0, 0, 0, 0,
			NULL, NULL, NULL, NULL, NULL);
}