#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* ipAddressChoice; } ;
struct TYPE_7__ {int /*<<< orphan*/  addressesOrRanges; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_3__ IPAddressFamily ;
typedef  int /*<<< orphan*/  IPAddrBlocks ;

/* Variables and functions */
 int /*<<< orphan*/  IPAddressFamily_cmp ; 
 int /*<<< orphan*/  X509v3_addr_get_afi (TYPE_3__*) ; 
 scalar_t__ X509v3_addr_inherits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  length_from_afi (int /*<<< orphan*/ ) ; 
 int sk_IPAddressFamily_find (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int sk_IPAddressFamily_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_IPAddressFamily_set_cmp_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_IPAddressFamily_value (int /*<<< orphan*/ *,int) ; 

int X509v3_addr_subset(IPAddrBlocks *a, IPAddrBlocks *b)
{
    int i;
    if (a == NULL || a == b)
        return 1;
    if (b == NULL || X509v3_addr_inherits(a) || X509v3_addr_inherits(b))
        return 0;
    (void)sk_IPAddressFamily_set_cmp_func(b, IPAddressFamily_cmp);
    for (i = 0; i < sk_IPAddressFamily_num(a); i++) {
        IPAddressFamily *fa = sk_IPAddressFamily_value(a, i);
        int j = sk_IPAddressFamily_find(b, fa);
        IPAddressFamily *fb;
        fb = sk_IPAddressFamily_value(b, j);
        if (fb == NULL)
            return 0;
        if (!addr_contains(fb->ipAddressChoice->u.addressesOrRanges,
                           fa->ipAddressChoice->u.addressesOrRanges,
                           length_from_afi(X509v3_addr_get_afi(fb))))
            return 0;
    }
    return 1;
}