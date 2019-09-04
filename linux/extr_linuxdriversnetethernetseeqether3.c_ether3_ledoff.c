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
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;
struct dev_priv {struct net_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  config2; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG2_CTRLO ; 
 int /*<<< orphan*/  REG_CONFIG2 ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 struct dev_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_2__* priv (struct net_device*) ; 
 struct dev_priv* private ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ether3_ledoff(struct timer_list *t)
{
	struct dev_priv *private = from_timer(private, t, timer);
	struct net_device *dev = private->dev;

	ether3_outw(priv(dev)->regs.config2 |= CFG2_CTRLO, REG_CONFIG2);
}