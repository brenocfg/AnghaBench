#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dn_fib_res {TYPE_2__* fi; int /*<<< orphan*/  prefixlen; } ;
typedef  int __le16 ;
struct TYPE_4__ {TYPE_1__* fib_nh; } ;
struct TYPE_3__ {int nh_gw; } ;

/* Variables and functions */
 int dnet_make_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le16 dn_fib_rules_map_destination(__le16 daddr, struct dn_fib_res *res)
{
	__le16 mask = dnet_make_mask(res->prefixlen);
	return (daddr&~mask)|res->fi->fib_nh->nh_gw;
}