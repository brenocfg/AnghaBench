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
struct TYPE_2__ {int /*<<< orphan*/  spiObjectIdx0; int /*<<< orphan*/  sysDevcon; int /*<<< orphan*/  sysConsole0; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_Tasks () ; 
 int /*<<< orphan*/  DRV_SPI_Tasks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_CONSOLE_Tasks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_DEVCON_Tasks (int /*<<< orphan*/ ) ; 
 TYPE_1__ sysObj ; 

void SYS_Tasks ( void )
{
    /* Maintain system services */
    SYS_CONSOLE_Tasks(sysObj.sysConsole0);
    SYS_DEVCON_Tasks(sysObj.sysDevcon);

    /* Maintain Device Drivers */
    DRV_SPI_Tasks(sysObj.spiObjectIdx0);

    /* Maintain Middleware & Other Libraries */
    
    /* Maintain the application's state machine. */
    APP_Tasks();
}