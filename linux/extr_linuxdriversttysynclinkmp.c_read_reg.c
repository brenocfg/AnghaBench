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
typedef  int /*<<< orphan*/  SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_REGADDR () ; 
 unsigned char* RegAddr ; 

__attribute__((used)) static unsigned char read_reg(SLMP_INFO * info, unsigned char Addr)
{
	CALC_REGADDR();
	return *RegAddr;
}