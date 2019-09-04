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
struct fusb300_ep_info {int /*<<< orphan*/  epnum; scalar_t__ bw_num; scalar_t__ interval; } ;
struct fusb300 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fusb300_set_bwnum (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  fusb300_set_ep_active (struct fusb300*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fusb300_set_epdir (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  fusb300_set_epmps (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  fusb300_set_eptype (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  fusb300_set_interval (struct fusb300*,struct fusb300_ep_info) ; 

__attribute__((used)) static void set_ep_reg(struct fusb300 *fusb300,
		      struct fusb300_ep_info info)
{
	fusb300_set_eptype(fusb300, info);
	fusb300_set_epdir(fusb300, info);
	fusb300_set_epmps(fusb300, info);

	if (info.interval)
		fusb300_set_interval(fusb300, info);

	if (info.bw_num)
		fusb300_set_bwnum(fusb300, info);

	fusb300_set_ep_active(fusb300, info.epnum);
}