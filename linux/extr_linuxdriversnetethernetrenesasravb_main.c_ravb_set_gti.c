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
typedef  unsigned long long uint64_t ;
struct ravb_private {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GTI ; 
 unsigned long long GTI_TIV_MAX ; 
 unsigned long long GTI_TIV_MIN ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_set_gti(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	struct device *dev = ndev->dev.parent;
	unsigned long rate;
	uint64_t inc;

	rate = clk_get_rate(priv->clk);
	if (!rate)
		return -EINVAL;

	inc = 1000000000ULL << 20;
	do_div(inc, rate);

	if (inc < GTI_TIV_MIN || inc > GTI_TIV_MAX) {
		dev_err(dev, "gti.tiv increment 0x%llx is outside the range 0x%x - 0x%x\n",
			inc, GTI_TIV_MIN, GTI_TIV_MAX);
		return -EINVAL;
	}

	ravb_write(ndev, inc, GTI);

	return 0;
}