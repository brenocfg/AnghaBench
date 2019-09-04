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
 int /*<<< orphan*/  DebugP_log0 (char*) ; 
 int /*<<< orphan*/  DebugP_log1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_DMA_clearErrorStatus () ; 
 int /*<<< orphan*/  MAP_DMA_getErrorStatus () ; 

__attribute__((used)) static void dmaErrorHwi(uintptr_t arg)
{
    DebugP_log1("DMA error code: %d\n", MAP_DMA_getErrorStatus());
    MAP_DMA_clearErrorStatus();
    DebugP_log0("DMA error!!\n");
    while(1);
}