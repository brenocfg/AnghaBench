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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UFSHCI_AHIBERN8_SCALE_FACTOR ; 
 int /*<<< orphan*/  UFSHCI_AHIBERN8_SCALE_MASK ; 
 int /*<<< orphan*/  UFSHCI_AHIBERN8_TIMER_MASK ; 

__attribute__((used)) static int ufshcd_ahit_to_us(u32 ahit)
{
	int timer = FIELD_GET(UFSHCI_AHIBERN8_TIMER_MASK, ahit);
	int scale = FIELD_GET(UFSHCI_AHIBERN8_SCALE_MASK, ahit);

	for (; scale > 0; --scale)
		timer *= UFSHCI_AHIBERN8_SCALE_FACTOR;

	return timer;
}