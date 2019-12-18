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

/* Variables and functions */
 int /*<<< orphan*/  DSL_DFE_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_PMU_DISABLE ; 
 int /*<<< orphan*/  PPE_EMA_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPE_SLL01_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPE_TC_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPE_TPE_PMU_SETUP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uninit_pmu(void)
{
    PPE_SLL01_PMU_SETUP(IFX_PMU_DISABLE);
    PPE_TC_PMU_SETUP(IFX_PMU_DISABLE);
    PPE_EMA_PMU_SETUP(IFX_PMU_DISABLE);
    //PPE_QSB_PMU_SETUP(IFX_PMU_DISABLE);
    PPE_TPE_PMU_SETUP(IFX_PMU_DISABLE);
    DSL_DFE_PMU_SETUP(IFX_PMU_DISABLE);
    //PPE_TOP_PMU_SETUP(IFX_PMU_DISABLE);
}