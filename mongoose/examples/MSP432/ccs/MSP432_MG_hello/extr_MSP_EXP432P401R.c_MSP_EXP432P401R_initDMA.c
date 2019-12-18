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
typedef  int /*<<< orphan*/  HwiP_Params ;
typedef  int /*<<< orphan*/ * HwiP_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  DebugP_log0 (char*) ; 
 int /*<<< orphan*/  HwiP_Params_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HwiP_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_DMA_ERR ; 
 int /*<<< orphan*/  MAP_DMA_enableModule () ; 
 int /*<<< orphan*/  MAP_DMA_setControlBase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaControlTable ; 
 int /*<<< orphan*/  dmaErrorHwi ; 
 int dmaInitialized ; 

void MSP_EXP432P401R_initDMA(void)
{
    HwiP_Params hwiParams;
    HwiP_Handle dmaErrorHwiHandle;

    if (!dmaInitialized) {
        HwiP_Params_init(&hwiParams);
        dmaErrorHwiHandle = HwiP_create(INT_DMA_ERR, dmaErrorHwi, &hwiParams);
        if (dmaErrorHwiHandle == NULL) {
            DebugP_log0("Failed to create DMA error Hwi!!\n");
            while (1);
        }

        MAP_DMA_enableModule();
        MAP_DMA_setControlBase(dmaControlTable);

        dmaInitialized = true;
    }
}