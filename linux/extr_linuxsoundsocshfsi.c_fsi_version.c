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
struct fsi_master {TYPE_1__* core; } ;
struct TYPE_2__ {int ver; } ;

/* Variables and functions */

__attribute__((used)) static int fsi_version(struct fsi_master *master)
{
	return master->core->ver;
}