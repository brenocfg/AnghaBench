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
struct phy_setting {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 struct phy_setting const* phy_lookup_setting (int,int,unsigned long*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const struct phy_setting *
phy_find_valid(int speed, int duplex, u32 supported)
{
	unsigned long mask = supported;

	return phy_lookup_setting(speed, duplex, &mask, BITS_PER_LONG, false);
}