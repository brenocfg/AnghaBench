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
struct aa_profile {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_newest_label (int /*<<< orphan*/ *) ; 
 struct aa_profile* labels_profile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct aa_profile *aa_get_newest_profile(struct aa_profile *p)
{
	return labels_profile(aa_get_newest_label(&p->label));
}