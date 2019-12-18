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
 long UTIME_NOW ; 
 long UTIME_OMIT ; 

__attribute__((used)) static bool nsec_valid(long nsec)
{
	if (nsec == UTIME_OMIT || nsec == UTIME_NOW)
		return true;

	return nsec >= 0 && nsec <= 999999999;
}