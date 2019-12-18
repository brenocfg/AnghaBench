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
struct extent_info {int dummy; } ;

/* Variables and functions */
 int __is_extent_mergeable (struct extent_info*,struct extent_info*) ; 

__attribute__((used)) static inline bool __is_front_mergeable(struct extent_info *cur,
						struct extent_info *front)
{
	return __is_extent_mergeable(cur, front);
}