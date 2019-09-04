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
struct lowpan_nhc {size_t nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** lowpan_nexthdr_nhcs ; 
 int /*<<< orphan*/  lowpan_nhc_lock ; 
 int /*<<< orphan*/  lowpan_nhc_remove (struct lowpan_nhc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void lowpan_nhc_del(struct lowpan_nhc *nhc)
{
	spin_lock_bh(&lowpan_nhc_lock);

	lowpan_nhc_remove(nhc);
	lowpan_nexthdr_nhcs[nhc->nexthdr] = NULL;

	spin_unlock_bh(&lowpan_nhc_lock);

	synchronize_net();
}