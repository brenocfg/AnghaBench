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
struct hw_xmit {scalar_t__ accnt; } ;

/* Variables and functions */

void rtw_init_hwxmits(struct hw_xmit *phwxmit, int entry)
{
	int i;

	for (i = 0; i < entry; i++, phwxmit++)
		phwxmit->accnt = 0;
}