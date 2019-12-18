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
struct flowidn {int daddr; int saddr; int flowidn_mark; int flowidn_scope; int flowidn_oif; int flowidn_iif; } ;

/* Variables and functions */

__attribute__((used)) static inline int compare_keys(struct flowidn *fl1, struct flowidn *fl2)
{
	return ((fl1->daddr ^ fl2->daddr) |
		(fl1->saddr ^ fl2->saddr) |
		(fl1->flowidn_mark ^ fl2->flowidn_mark) |
		(fl1->flowidn_scope ^ fl2->flowidn_scope) |
		(fl1->flowidn_oif ^ fl2->flowidn_oif) |
		(fl1->flowidn_iif ^ fl2->flowidn_iif)) == 0;
}