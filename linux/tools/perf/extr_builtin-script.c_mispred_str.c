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
struct TYPE_2__ {scalar_t__ predicted; scalar_t__ mispred; } ;
struct branch_entry {TYPE_1__ flags; } ;

/* Variables and functions */

__attribute__((used)) static inline char
mispred_str(struct branch_entry *br)
{
	if (!(br->flags.mispred  || br->flags.predicted))
		return '-';

	return br->flags.predicted ? 'P' : 'M';
}