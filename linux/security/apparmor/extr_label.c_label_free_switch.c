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
struct aa_label {int flags; } ;

/* Variables and functions */
 int FLAG_NS_COUNT ; 
 int /*<<< orphan*/  aa_free_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_free_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_label_free (struct aa_label*) ; 
 scalar_t__ label_isprofile (struct aa_label*) ; 
 int /*<<< orphan*/  labels_ns (struct aa_label*) ; 
 int /*<<< orphan*/  labels_profile (struct aa_label*) ; 

__attribute__((used)) static void label_free_switch(struct aa_label *label)
{
	if (label->flags & FLAG_NS_COUNT)
		aa_free_ns(labels_ns(label));
	else if (label_isprofile(label))
		aa_free_profile(labels_profile(label));
	else
		aa_label_free(label);
}