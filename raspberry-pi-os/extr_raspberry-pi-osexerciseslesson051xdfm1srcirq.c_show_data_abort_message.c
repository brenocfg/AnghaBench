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
 int /*<<< orphan*/  exit_process () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void show_data_abort_message(unsigned long esr, unsigned long address)
{
	printf("Data abort exception, ESR:%x, fault address: %x\r\n", esr, address);
	printf("terminating faulting process...\r\n");
	exit_process();
}