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
struct rtl8366_smi {int /*<<< orphan*/  sw_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8366s_switch_cleanup(struct rtl8366_smi *smi)
{
	unregister_switch(&smi->sw_dev);
}