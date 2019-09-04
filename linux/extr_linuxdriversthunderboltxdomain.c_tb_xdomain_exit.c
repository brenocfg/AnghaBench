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

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_property_free_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdomain_property_block ; 
 int /*<<< orphan*/  xdomain_property_dir ; 

void tb_xdomain_exit(void)
{
	kfree(xdomain_property_block);
	tb_property_free_dir(xdomain_property_dir);
}