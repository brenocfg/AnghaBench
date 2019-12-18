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
struct TYPE_2__ {unsigned long rate; } ;
struct fsi_priv {TYPE_1__ clock; } ;

/* Variables and functions */

__attribute__((used)) static void fsi_clk_valid(struct fsi_priv *fsi, unsigned long rate)
{
	fsi->clock.rate = rate;
}