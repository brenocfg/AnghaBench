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
struct fsi_clk {int /*<<< orphan*/  div; int /*<<< orphan*/  ick; int /*<<< orphan*/  xck; int /*<<< orphan*/  count; } ;
struct fsi_priv {struct fsi_clk clock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_clk_is_valid (struct fsi_priv*) ; 

__attribute__((used)) static int fsi_clk_disable(struct device *dev,
			    struct fsi_priv *fsi)
{
	struct fsi_clk *clock = &fsi->clock;

	if (!fsi_clk_is_valid(fsi))
		return -EINVAL;

	if (1 == clock->count--) {
		clk_disable(clock->xck);
		clk_disable(clock->ick);
		clk_disable(clock->div);
	}

	return 0;
}