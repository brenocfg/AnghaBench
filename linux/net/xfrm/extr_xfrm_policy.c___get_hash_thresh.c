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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {TYPE_1__* policy_bydst; } ;
struct net {TYPE_2__ xfrm; } ;
struct TYPE_3__ {int /*<<< orphan*/  sbits6; int /*<<< orphan*/  dbits6; int /*<<< orphan*/  sbits4; int /*<<< orphan*/  dbits4; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

__attribute__((used)) static void __get_hash_thresh(struct net *net,
			      unsigned short family, int dir,
			      u8 *dbits, u8 *sbits)
{
	switch (family) {
	case AF_INET:
		*dbits = net->xfrm.policy_bydst[dir].dbits4;
		*sbits = net->xfrm.policy_bydst[dir].sbits4;
		break;

	case AF_INET6:
		*dbits = net->xfrm.policy_bydst[dir].dbits6;
		*sbits = net->xfrm.policy_bydst[dir].sbits6;
		break;

	default:
		*dbits = 0;
		*sbits = 0;
	}
}