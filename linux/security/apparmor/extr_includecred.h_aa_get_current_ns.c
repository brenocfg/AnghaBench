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
struct aa_ns {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  labels_ns (struct aa_label*) ; 

__attribute__((used)) static inline struct aa_ns *aa_get_current_ns(void)
{
	struct aa_label *label;
	struct aa_ns *ns;

	label  = __begin_current_label_crit_section();
	ns = aa_get_ns(labels_ns(label));
	__end_current_label_crit_section(label);

	return ns;
}