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
struct wiphy {int regulatory_flags; } ;

/* Variables and functions */
 int REGULATORY_CUSTOM_REG ; 
 int REGULATORY_STRICT_REG ; 

__attribute__((used)) static bool wiphy_strict_alpha2_regd(struct wiphy *wiphy)
{
	if (wiphy->regulatory_flags & REGULATORY_STRICT_REG &&
	    !(wiphy->regulatory_flags & REGULATORY_CUSTOM_REG))
		return true;
	return false;
}