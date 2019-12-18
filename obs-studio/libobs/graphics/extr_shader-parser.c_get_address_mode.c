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
typedef  enum gs_address_mode { ____Placeholder_gs_address_mode } gs_address_mode ;

/* Variables and functions */
 int GS_ADDRESS_BORDER ; 
 int GS_ADDRESS_CLAMP ; 
 int GS_ADDRESS_MIRROR ; 
 int GS_ADDRESS_MIRRORONCE ; 
 int GS_ADDRESS_WRAP ; 
 scalar_t__ astrcmpi (char const*,char*) ; 

extern enum gs_address_mode get_address_mode(const char *mode)
{
	if (astrcmpi(mode, "Wrap") == 0 || astrcmpi(mode, "Repeat") == 0)
		return GS_ADDRESS_WRAP;
	else if (astrcmpi(mode, "Clamp") == 0 || astrcmpi(mode, "None") == 0)
		return GS_ADDRESS_CLAMP;
	else if (astrcmpi(mode, "Mirror") == 0)
		return GS_ADDRESS_MIRROR;
	else if (astrcmpi(mode, "Border") == 0)
		return GS_ADDRESS_BORDER;
	else if (astrcmpi(mode, "MirrorOnce") == 0)
		return GS_ADDRESS_MIRRORONCE;

	return GS_ADDRESS_CLAMP;
}