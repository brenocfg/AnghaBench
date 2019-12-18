#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pbus; } ;
struct TYPE_6__ {TYPE_2__ pbus; } ;
struct snd_hal2 {TYPE_3__ adc; } ;
struct TYPE_4__ {int /*<<< orphan*/  pbdma_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPC3_PDMACTRL_LD ; 

__attribute__((used)) static inline void hal2_stop_adc(struct snd_hal2 *hal2)
{
	hal2->adc.pbus.pbus->pbdma_ctrl = HPC3_PDMACTRL_LD;
}