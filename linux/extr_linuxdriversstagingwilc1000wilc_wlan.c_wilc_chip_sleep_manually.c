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
struct wilc {TYPE_1__* hif_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hif_write_reg ) (struct wilc*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_ONLY ; 
 scalar_t__ CHIP_SLEEPING_MANUAL ; 
 scalar_t__ CHIP_WAKEDUP ; 
 int /*<<< orphan*/  RELEASE_ONLY ; 
 int /*<<< orphan*/  acquire_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip_allow_sleep (struct wilc*) ; 
 scalar_t__ chip_ps_state ; 
 int /*<<< orphan*/  release_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wilc*,int,int) ; 

void wilc_chip_sleep_manually(struct wilc *wilc)
{
	if (chip_ps_state != CHIP_WAKEDUP)
		return;
	acquire_bus(wilc, ACQUIRE_ONLY);

	chip_allow_sleep(wilc);
	wilc->hif_func->hif_write_reg(wilc, 0x10a8, 1);

	chip_ps_state = CHIP_SLEEPING_MANUAL;
	release_bus(wilc, RELEASE_ONLY);
}