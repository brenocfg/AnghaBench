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
typedef  int /*<<< orphan*/  spl_dual_it_object ;

/* Variables and functions */
 int spl_dual_it_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int spl_caching_it_has_next(spl_dual_it_object *intern)
{
	return spl_dual_it_valid(intern);
}