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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (struct device*,char const*) ; 

__attribute__((used)) static struct clk *get_optional_clk(struct device *dev, const char *id)
{
	struct clk *opt_clk;

	opt_clk = devm_clk_get(dev, id);
	/* ignore error number except EPROBE_DEFER */
	if (IS_ERR(opt_clk) && (PTR_ERR(opt_clk) != -EPROBE_DEFER))
		opt_clk = NULL;

	return opt_clk;
}