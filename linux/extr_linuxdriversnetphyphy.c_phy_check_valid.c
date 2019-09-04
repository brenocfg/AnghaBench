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
typedef  unsigned long u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int /*<<< orphan*/  phy_lookup_setting (int,int,unsigned long*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool phy_check_valid(int speed, int duplex, u32 features)
{
	unsigned long mask = features;

	return !!phy_lookup_setting(speed, duplex, &mask, BITS_PER_LONG, true);
}