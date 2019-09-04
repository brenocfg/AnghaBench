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
struct iface {scalar_t__ iflink; scalar_t__ ifindex; } ;

/* Variables and functions */

int iface_is_eligible(struct iface *iface) {
    if(iface->iflink != iface->ifindex)
        return 1;

    return 0;
}