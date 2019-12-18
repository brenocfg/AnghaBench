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
 int /*<<< orphan*/  AT91F_InitSdram () ; 

__attribute__((used)) static void AT91F_InitMemories()
{
	int *pEbi = (int *)0xFFFFFF60;

	//* Setup MEMC to support all connected memories (CS0 = FLASH; CS1=SDRAM)
	pEbi  = (int *)0xFFFFFF60;
	*pEbi = 0x00000002;

	//* CS0 cs for flash
	pEbi  = (int *)0xFFFFFF70;
	*pEbi = 0x00003284;
	
	AT91F_InitSdram();
}