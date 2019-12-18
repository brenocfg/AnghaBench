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
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_label* aa_current_raw_label () ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 

__attribute__((used)) static inline void end_current_label_crit_section(struct aa_label *label)
{
	if (label != aa_current_raw_label())
		aa_put_label(label);
}