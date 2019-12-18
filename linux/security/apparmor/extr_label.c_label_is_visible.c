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
struct aa_profile {int /*<<< orphan*/  ns; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int aa_ns_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  labels_ns (struct aa_label*) ; 

__attribute__((used)) static inline bool label_is_visible(struct aa_profile *profile,
				    struct aa_label *label)
{
	return aa_ns_visible(profile->ns, labels_ns(label), true);
}