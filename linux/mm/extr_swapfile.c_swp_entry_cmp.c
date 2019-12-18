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
typedef  int /*<<< orphan*/  swp_entry_t ;

/* Variables and functions */
 scalar_t__ swp_type (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int swp_entry_cmp(const void *ent1, const void *ent2)
{
	const swp_entry_t *e1 = ent1, *e2 = ent2;

	return (int)swp_type(*e1) - (int)swp_type(*e2);
}