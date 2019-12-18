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
typedef  enum vlan_acceptable_frames { ____Placeholder_vlan_acceptable_frames } vlan_acceptable_frames ;

/* Variables and functions */
#define  VLAN_ALL 130 
#define  VLAN_ONLY_TAGGED 129 
#define  VLAN_ONLY_UNTAGGED_OR_PRIORITY 128 

__attribute__((used)) static const char *
print_vlan_accept(enum vlan_acceptable_frames mode)
{
    switch (mode)
    {
        case VLAN_ONLY_TAGGED:
            return "tagged";
        case VLAN_ONLY_UNTAGGED_OR_PRIORITY:
            return "untagged";
        case VLAN_ALL:
            return "all";
    }
    return NULL;
}