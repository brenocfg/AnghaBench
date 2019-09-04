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
struct aa_label {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct aa_label *__aa_get_label(struct aa_label *l)
{
	if (l && kref_get_unless_zero(&l->count))
		return l;

	return NULL;
}