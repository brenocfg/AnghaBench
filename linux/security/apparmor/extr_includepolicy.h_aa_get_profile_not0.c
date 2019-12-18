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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct aa_profile {TYPE_1__ label; } ;

/* Variables and functions */
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct aa_profile *aa_get_profile_not0(struct aa_profile *p)
{
	if (p && kref_get_unless_zero(&p->label.count))
		return p;

	return NULL;
}