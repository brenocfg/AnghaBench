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
struct TYPE_2__ {int /*<<< orphan*/  tcpip; int /*<<< orphan*/  drvUsart0; int /*<<< orphan*/  sysTmr; int /*<<< orphan*/  sysDevcon; int /*<<< orphan*/  sysConsole0; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_Tasks () ; 
 int /*<<< orphan*/  DRV_USART_TasksError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_USART_TasksReceive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_USART_TasksTransmit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_CMD_Tasks () ; 
 int /*<<< orphan*/  SYS_CONSOLE_Tasks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_DEVCON_Tasks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_TMR_Tasks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPIP_STACK_Task (int /*<<< orphan*/ ) ; 
 TYPE_1__ sysObj ; 

void SYS_Tasks ( void )
{
    /* Maintain system services */
    /* SYS_COMMAND layer tasks routine */
    SYS_CMD_Tasks();
    SYS_CONSOLE_Tasks(sysObj.sysConsole0);
    SYS_DEVCON_Tasks(sysObj.sysDevcon);
    /* SYS_TMR Device layer tasks routine */
    SYS_TMR_Tasks(sysObj.sysTmr);

    /* Maintain Device Drivers */
    DRV_USART_TasksTransmit(sysObj.drvUsart0);
    DRV_USART_TasksReceive(sysObj.drvUsart0);
    DRV_USART_TasksError (sysObj.drvUsart0);

    /* Maintain Middleware & Other Libraries */
    /* Maintain the TCP/IP Stack*/
    TCPIP_STACK_Task(sysObj.tcpip);

    /* Maintain the application's state machine. */
    APP_Tasks();
}