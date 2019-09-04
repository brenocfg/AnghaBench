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
struct fsi_priv {int clk_master; } ;

/* Variables and functions */

__attribute__((used)) static int fsi_is_clk_master(struct fsi_priv *fsi)
{
	return fsi->clk_master;
}