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
struct TYPE_2__ {scalar_t__ tcpip; int /*<<< orphan*/  sysTmr; int /*<<< orphan*/  sysDebug; int /*<<< orphan*/  sysConsole0; int /*<<< orphan*/  drvUsart0; int /*<<< orphan*/  drvTmr0; int /*<<< orphan*/  spiObjectIdx0; int /*<<< orphan*/  sysDevcon; } ;
typedef  int /*<<< orphan*/  SYS_MODULE_INIT ;

/* Variables and functions */
 int /*<<< orphan*/  APP_Initialize () ; 
 int /*<<< orphan*/  BSP_Initialize () ; 
 int /*<<< orphan*/  DRV_SPI_INDEX_0 ; 
 int /*<<< orphan*/  DRV_SPI_INT_PRIORITY_IDX0 ; 
 int /*<<< orphan*/  DRV_SPI_INT_SUB_PRIORITY_IDX0 ; 
 int /*<<< orphan*/  DRV_SPI_INT_VECTOR_IDX0 ; 
 int /*<<< orphan*/  DRV_SPI_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  DRV_TMR_INDEX_0 ; 
 int /*<<< orphan*/  DRV_TMR_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRV_USART_INDEX_0 ; 
 int /*<<< orphan*/  DRV_USART_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_PRIORITY_LEVEL1 ; 
 int /*<<< orphan*/  INT_PRIORITY_LEVEL5 ; 
 int /*<<< orphan*/  INT_SUBPRIORITY_LEVEL0 ; 
 int /*<<< orphan*/  INT_SUBPRIORITY_LEVEL3 ; 
 int /*<<< orphan*/  INT_VECTOR_ETH ; 
 int /*<<< orphan*/  INT_VECTOR_T1 ; 
 int /*<<< orphan*/  SYS_ASSERT (int,char*) ; 
 int /*<<< orphan*/  SYS_CLK_Initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CLK_SystemFrequencyGet () ; 
 int /*<<< orphan*/  SYS_CMD_Initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CONSOLE_INDEX_0 ; 
 int /*<<< orphan*/  SYS_CONSOLE_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_DEBUG_INDEX_0 ; 
 int /*<<< orphan*/  SYS_DEBUG_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_DEVCON_INDEX_0 ; 
 int /*<<< orphan*/  SYS_DEVCON_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_DEVCON_JTAGDisable () ; 
 int /*<<< orphan*/  SYS_DEVCON_PerformanceConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_Enable () ; 
 int /*<<< orphan*/  SYS_INT_Initialize () ; 
 int /*<<< orphan*/  SYS_INT_VectorPrioritySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_VectorSubprioritySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_MODULE_OBJ_INVALID ; 
 int /*<<< orphan*/  SYS_PORTS_Initialize () ; 
 int /*<<< orphan*/  SYS_RANDOM_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_TMR_INDEX_0 ; 
 int /*<<< orphan*/  SYS_TMR_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const) ; 
 scalar_t__ TCPIP_STACK_Init () ; 
 int /*<<< orphan*/  consUsartInit0 ; 
 int /*<<< orphan*/  debugInit ; 
 int /*<<< orphan*/  drvSpi0InitData ; 
 int /*<<< orphan*/  drvTmr0InitData ; 
 int /*<<< orphan*/  drvUsart0InitData ; 
 int /*<<< orphan*/  sysCmdInit ; 
 int /*<<< orphan*/  sysDevconInit ; 
 TYPE_1__ sysObj ; 
 int /*<<< orphan*/  sysTmrInitData ; 

void SYS_Initialize ( void* data )
{
    /* Core Processor Initialization */
    SYS_CLK_Initialize( NULL );
    sysObj.sysDevcon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)&sysDevconInit);
    SYS_DEVCON_PerformanceConfig(SYS_CLK_SystemFrequencyGet());
    SYS_DEVCON_JTAGDisable();
    SYS_PORTS_Initialize();
    /* Board Support Package Initialization */
    BSP_Initialize();

    /* Initialize Drivers */

    /*** SPI Driver Index 0 initialization***/

    SYS_INT_VectorPrioritySet(DRV_SPI_INT_VECTOR_IDX0, DRV_SPI_INT_PRIORITY_IDX0);
    SYS_INT_VectorSubprioritySet(DRV_SPI_INT_VECTOR_IDX0, DRV_SPI_INT_SUB_PRIORITY_IDX0);
    sysObj.spiObjectIdx0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (const SYS_MODULE_INIT  * const)&drvSpi0InitData);

    sysObj.drvTmr0 = DRV_TMR_Initialize(DRV_TMR_INDEX_0, (SYS_MODULE_INIT *)&drvTmr0InitData);

    SYS_INT_VectorPrioritySet(INT_VECTOR_T1, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T1, INT_SUBPRIORITY_LEVEL0);


     sysObj.drvUsart0 = DRV_USART_Initialize(DRV_USART_INDEX_0, (SYS_MODULE_INIT *)&drvUsart0InitData);

    /* Initialize System Services */

    /*** Command Service Initialization Code ***/
    SYS_CMD_Initialize((SYS_MODULE_INIT*)&sysCmdInit);
    sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&consUsartInit0);


    /*** Debug Service Initialization Code ***/
    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();

    /*** Random Service Initialization Code ***/
    SYS_RANDOM_Initialize(0, 0);

    /*** TMR Service Initialization Code ***/
    sysObj.sysTmr  = SYS_TMR_Initialize(SYS_TMR_INDEX_0, (const SYS_MODULE_INIT  * const)&sysTmrInitData);

    /* Initialize Middleware */

    /* set priority for ETHERNET interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_ETH, INT_PRIORITY_LEVEL5);

    /* set sub-priority for ETHERNET interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_ETH, INT_SUBPRIORITY_LEVEL3);

    /* TCPIP Stack Initialization */
    sysObj.tcpip = TCPIP_STACK_Init();
    SYS_ASSERT(sysObj.tcpip != SYS_MODULE_OBJ_INVALID, "TCPIP_STACK_Init Failed" );


    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize();
}