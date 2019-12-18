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
struct tep_handle {int flags; } ;
typedef  enum tep_flag { ____Placeholder_tep_flag } tep_flag ;

/* Variables and functions */

void tep_clear_flag(struct tep_handle *tep, enum tep_flag flag)
{
	if (tep)
		tep->flags &= ~flag;
}