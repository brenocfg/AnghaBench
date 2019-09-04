#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ipAddressChoice; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_2__ IPAddressFamily ;
typedef  int /*<<< orphan*/  IPAddrBlocks ;

/* Variables and functions */
 scalar_t__ IPAddressChoice_inherit ; 
 int sk_IPAddressFamily_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_IPAddressFamily_value (int /*<<< orphan*/ *,int) ; 

int X509v3_addr_inherits(IPAddrBlocks *addr)
{
    int i;
    if (addr == NULL)
        return 0;
    for (i = 0; i < sk_IPAddressFamily_num(addr); i++) {
        IPAddressFamily *f = sk_IPAddressFamily_value(addr, i);
        if (f->ipAddressChoice->type == IPAddressChoice_inherit)
            return 1;
    }
    return 0;
}