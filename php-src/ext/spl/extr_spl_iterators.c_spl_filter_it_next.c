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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  spl_dual_it_object ;

/* Variables and functions */
 int /*<<< orphan*/  spl_dual_it_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spl_filter_it_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void spl_filter_it_next(zval *zthis, spl_dual_it_object *intern)
{
	spl_dual_it_next(intern, 1);
	spl_filter_it_fetch(zthis, intern);
}