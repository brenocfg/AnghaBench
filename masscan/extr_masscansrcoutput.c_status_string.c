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
typedef  enum PortStatus { ____Placeholder_PortStatus } PortStatus ;

/* Variables and functions */
#define  PortStatus_Arp 130 
#define  PortStatus_Closed 129 
#define  PortStatus_Open 128 

const char *
status_string(enum PortStatus status)
{
    switch (status) {
        case PortStatus_Open: return "open";
        case PortStatus_Closed: return "closed";
        case PortStatus_Arp: return "up";
        default: return "unknown";
    }
}