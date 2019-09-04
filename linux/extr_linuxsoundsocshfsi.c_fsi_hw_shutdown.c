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
struct fsi_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int fsi_clk_disable (struct device*,struct fsi_priv*) ; 
 scalar_t__ fsi_is_clk_master (struct fsi_priv*) ; 

__attribute__((used)) static int fsi_hw_shutdown(struct fsi_priv *fsi,
			    struct device *dev)
{
	/* stop master clock */
	if (fsi_is_clk_master(fsi))
		return fsi_clk_disable(dev, fsi);

	return 0;
}