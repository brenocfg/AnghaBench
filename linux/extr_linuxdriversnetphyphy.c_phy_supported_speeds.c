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
struct phy_device {unsigned long supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 unsigned int phy_speeds (unsigned int*,unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 

unsigned int phy_supported_speeds(struct phy_device *phy,
				  unsigned int *speeds,
				  unsigned int size)
{
	unsigned long supported = phy->supported;

	return phy_speeds(speeds, size, &supported, BITS_PER_LONG);
}