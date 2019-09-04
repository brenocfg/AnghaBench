#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ expires; } ;
struct TYPE_5__ {int config2; } ;
struct TYPE_6__ {TYPE_1__ regs; TYPE_3__ timer; } ;

/* Variables and functions */
 int CFG2_CTRLO ; 
 int HZ ; 
 int /*<<< orphan*/  REG_CONFIG2 ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_2__* priv (struct net_device*) ; 

__attribute__((used)) static inline void ether3_ledon(struct net_device *dev)
{
	del_timer(&priv(dev)->timer);
	priv(dev)->timer.expires = jiffies + HZ / 50; /* leave on for 1/50th second */
	add_timer(&priv(dev)->timer);
	if (priv(dev)->regs.config2 & CFG2_CTRLO)
		ether3_outw(priv(dev)->regs.config2 &= ~CFG2_CTRLO, REG_CONFIG2);
}