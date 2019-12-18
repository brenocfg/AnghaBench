#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pktgen_dev {TYPE_1__* flows; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int F_INIT ; 

__attribute__((used)) static inline int f_seen(const struct pktgen_dev *pkt_dev, int flow)
{
	return !!(pkt_dev->flows[flow].flags & F_INIT);
}