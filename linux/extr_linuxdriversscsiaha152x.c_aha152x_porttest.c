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
 int GETPORT (scalar_t__) ; 
 scalar_t__ O_DMACNTRL1 ; 
 scalar_t__ O_STACK ; 
 int /*<<< orphan*/  SETPORT (scalar_t__,int) ; 

__attribute__((used)) static int aha152x_porttest(int io_port)
{
	int i;

	SETPORT(io_port + O_DMACNTRL1, 0);	/* reset stack pointer */
	for (i = 0; i < 16; i++)
		SETPORT(io_port + O_STACK, i);

	SETPORT(io_port + O_DMACNTRL1, 0);	/* reset stack pointer */
	for (i = 0; i < 16 && GETPORT(io_port + O_STACK) == i; i++)
		;

	return (i == 16);
}