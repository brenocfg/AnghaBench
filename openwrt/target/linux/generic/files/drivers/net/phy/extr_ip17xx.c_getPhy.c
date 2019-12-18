#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ip17xx_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ reg ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  REG_SUPP (TYPE_1__) ; 
 int ip_phy_read (struct ip17xx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getPhy(struct ip17xx_state *state, reg mii)
{
	if (!REG_SUPP(mii))
		return -EFAULT;
	return ip_phy_read(state, mii.p, mii.m);
}