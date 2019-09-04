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
struct cp_private {TYPE_2__* dev; } ;
struct TYPE_3__ {int rx_missed_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RxMissed ; 
 int cpr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cp_get_stats(struct cp_private *cp)
{
	/* only lower 24 bits valid; write any value to clear */
	cp->dev->stats.rx_missed_errors += (cpr32 (RxMissed) & 0xffffff);
	cpw32 (RxMissed, 0);
}