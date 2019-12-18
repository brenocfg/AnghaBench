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
 int /*<<< orphan*/  free_iface (struct iface*) ; 

void free_host_ifaces(struct iface *iface) {
    while(iface) {
        struct iface *t = iface->next;
        free_iface(iface);
        iface = t;
    }
}