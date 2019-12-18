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
 int /*<<< orphan*/  OFS_LINE_STATUS ; 
 int UART16550_READ (int /*<<< orphan*/ ) ; 

int serial_tstc (void)
{
    return(UART16550_READ(OFS_LINE_STATUS) & 0x1);
}