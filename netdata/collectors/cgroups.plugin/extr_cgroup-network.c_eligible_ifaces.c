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
struct iface {struct iface* next; } ;

/* Variables and functions */
 scalar_t__ iface_is_eligible (struct iface*) ; 

int eligible_ifaces(struct iface *root) {
    int eligible = 0;

    struct iface *t;
    for(t = root; t ; t = t->next)
        if(iface_is_eligible(t))
            eligible++;

    return eligible;
}