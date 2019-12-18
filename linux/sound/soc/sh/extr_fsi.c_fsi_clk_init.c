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
struct fsi_clk {int (* set_rate ) (struct device*,struct fsi_priv*) ;int /*<<< orphan*/ * own; int /*<<< orphan*/ * div; int /*<<< orphan*/ * ick; int /*<<< orphan*/ * xck; scalar_t__ count; scalar_t__ rate; } ;
struct fsi_priv {struct fsi_clk clock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int fsi_is_port_a (struct fsi_priv*) ; 

__attribute__((used)) static int fsi_clk_init(struct device *dev,
			struct fsi_priv *fsi,
			int xck,
			int ick,
			int div,
			int (*set_rate)(struct device *dev,
					struct fsi_priv *fsi))
{
	struct fsi_clk *clock = &fsi->clock;
	int is_porta = fsi_is_port_a(fsi);

	clock->xck	= NULL;
	clock->ick	= NULL;
	clock->div	= NULL;
	clock->rate	= 0;
	clock->count	= 0;
	clock->set_rate	= set_rate;

	clock->own = devm_clk_get(dev, NULL);
	if (IS_ERR(clock->own))
		return -EINVAL;

	/* external clock */
	if (xck) {
		clock->xck = devm_clk_get(dev, is_porta ? "xcka" : "xckb");
		if (IS_ERR(clock->xck)) {
			dev_err(dev, "can't get xck clock\n");
			return -EINVAL;
		}
		if (clock->xck == clock->own) {
			dev_err(dev, "cpu doesn't support xck clock\n");
			return -EINVAL;
		}
	}

	/* FSIACLK/FSIBCLK */
	if (ick) {
		clock->ick = devm_clk_get(dev,  is_porta ? "icka" : "ickb");
		if (IS_ERR(clock->ick)) {
			dev_err(dev, "can't get ick clock\n");
			return -EINVAL;
		}
		if (clock->ick == clock->own) {
			dev_err(dev, "cpu doesn't support ick clock\n");
			return -EINVAL;
		}
	}

	/* FSI-DIV */
	if (div) {
		clock->div = devm_clk_get(dev,  is_porta ? "diva" : "divb");
		if (IS_ERR(clock->div)) {
			dev_err(dev, "can't get div clock\n");
			return -EINVAL;
		}
		if (clock->div == clock->own) {
			dev_err(dev, "cpu doesn't support div clock\n");
			return -EINVAL;
		}
	}

	return 0;
}