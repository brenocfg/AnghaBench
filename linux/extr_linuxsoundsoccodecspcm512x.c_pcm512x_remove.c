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
struct pcm512x_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  sclk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct pcm512x_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pcm512x_remove(struct device *dev)
{
	struct pcm512x_priv *pcm512x = dev_get_drvdata(dev);

	pm_runtime_disable(dev);
	if (!IS_ERR(pcm512x->sclk))
		clk_disable_unprepare(pcm512x->sclk);
	regulator_bulk_disable(ARRAY_SIZE(pcm512x->supplies),
			       pcm512x->supplies);
}