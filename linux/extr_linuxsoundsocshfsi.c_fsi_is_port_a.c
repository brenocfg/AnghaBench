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
struct fsi_priv {scalar_t__ base; TYPE_1__* master; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */

__attribute__((used)) static int fsi_is_port_a(struct fsi_priv *fsi)
{
	return fsi->master->base == fsi->base;
}