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
struct TYPE_2__ {int /*<<< orphan*/  sysDebug; int /*<<< orphan*/  sysConsole0; int /*<<< orphan*/  drvUsart0; int /*<<< orphan*/  spiObjectIdx0; int /*<<< orphan*/  sysDevcon; } ;
typedef  int /*<<< orphan*/  SYS_MODULE_INIT ;

/* Variables and functions */
 int /*<<< orphan*/  APP_Initialize () ; 
 int /*<<< orphan*/  DRV_RTCC_Initialize () ; 
 int /*<<< orphan*/  DRV_SPI_INDEX_0 ; 
 int /*<<< orphan*/  DRV_SPI_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  DRV_USART_INDEX_0 ; 
 int /*<<< orphan*/  DRV_USART_Initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_PRIORITY_LEVEL3 ; 
 int /*<<< orphan*/  INT_SUBPRIORITY_LEVEL0 ; 
 int /*<<< orphan*/  INT_VECTOR_UART2 ; 
 int /*<<< orphan*/  SYS_CLK_Initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CLK_SystemFrequencyGet () ; 
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
 int /*<<< orphan*/  SYS_PORTS_Initialize () ; 
 int /*<<< orphan*/  debugInit ; 
 int /*<<< orphan*/  sysDevconInit ; 
 TYPE_1__ sysObj ; 

void SYS_Initialize ( void* data )
{
    /* Core Processor Initialization */
    SYS_CLK_Initialize( NULL );
    sysObj.sysDevcon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)&sysDevconInit);
    SYS_DEVCON_PerformanceConfig(SYS_CLK_SystemFrequencyGet());
    SYS_DEVCON_JTAGDisable();
    SYS_PORTS_Initialize();

    /* Initialize Drivers */

    /*** SPI Driver Index 0 initialization***/

    sysObj.spiObjectIdx0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (const SYS_MODULE_INIT  * const)NULL);
    /* RTCC Initialization Call */
    DRV_RTCC_Initialize();

    sysObj.drvUsart0 = DRV_USART_Initialize(DRV_USART_INDEX_0, (SYS_MODULE_INIT *)NULL);
    SYS_INT_VectorPrioritySet(INT_VECTOR_UART2, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_UART2, INT_SUBPRIORITY_LEVEL0);

    /* Initialize System Services */
    sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, NULL);


    /*** Debug Service Initialization Code ***/
    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();
  
    /* Initialize Middleware */

    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize();
}