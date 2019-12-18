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
struct TYPE_2__ {scalar_t__ rate; scalar_t__ set_rate; } ;
struct fsi_priv {TYPE_1__ clock; } ;

/* Variables and functions */

__attribute__((used)) static int fsi_clk_is_valid(struct fsi_priv *fsi)
{
	return	fsi->clock.set_rate &&
		fsi->clock.rate;
}