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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_tmr_ioport ; 

__attribute__((used)) static u32 read_pmtmr(void)
{
	u32 v1=0,v2=0,v3=0;
	/* It has been reported that because of various broken
	 * chipsets (ICH4, PIIX4 and PIIX4E) where the ACPI PM time
	 * source is not latched, so you must read it multiple
	 * times to insure a safe value is read.
	 */
	do {
		v1 = inl(pm_tmr_ioport);
		v2 = inl(pm_tmr_ioport);
		v3 = inl(pm_tmr_ioport);
	} while ((v1 > v2 && v1 < v3) || (v2 > v3 && v2 < v1)
		 || (v3 > v1 && v3 < v2));

	/* mask the output to 24 bits */
	return (v2 & 0xFFFFFF);
}