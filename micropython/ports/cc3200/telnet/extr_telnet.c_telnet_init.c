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
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * rxBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_TELNET_STE_DISABLED ; 
 int /*<<< orphan*/  TELNET_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/ * mem_Malloc (int /*<<< orphan*/ ) ; 
 TYPE_1__ telnet_data ; 

void telnet_init (void) {
    // Allocate memory for the receive buffer (from the RTOS heap)
    ASSERT ((telnet_data.rxBuffer = mem_Malloc(TELNET_RX_BUFFER_SIZE)) != NULL);
    telnet_data.state = E_TELNET_STE_DISABLED;
}