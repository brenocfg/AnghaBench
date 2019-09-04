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
struct fusb300_ep_info {int /*<<< orphan*/  epnum; } ;
struct fusb300 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fusb300_set_epaddrofs (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  fusb300_set_fifo_entry (struct fusb300*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fusb300_set_start_entry (struct fusb300*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep_fifo_setting(struct fusb300 *fusb300,
			    struct fusb300_ep_info info)
{
	fusb300_set_fifo_entry(fusb300, info.epnum);
	fusb300_set_start_entry(fusb300, info.epnum);
	fusb300_set_epaddrofs(fusb300, info);
}