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
 struct aa_label* aa_get_newest_label (struct aa_label*) ; 
 scalar_t__ label_is_stale (struct aa_label*) ; 

__attribute__((used)) static inline struct aa_label *__begin_current_label_crit_section(void)
{
	struct aa_label *label = aa_current_raw_label();

	if (label_is_stale(label))
		label = aa_get_newest_label(label);

	return label;
}