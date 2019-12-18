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
#define  TOP_NET30 131 
#define  TOP_P2P 130 
#define  TOP_SUBNET 129 
#define  TOP_UNDEF 128 

const char *
print_topology(const int topology)
{
    switch (topology)
    {
        case TOP_UNDEF:
            return "undef";

        case TOP_NET30:
            return "net30";

        case TOP_P2P:
            return "p2p";

        case TOP_SUBNET:
            return "subnet";

        default:
            return "unknown";
    }
}