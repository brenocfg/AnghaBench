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
struct exofs_i_info {int dummy; } ;

/* Variables and functions */
 int __exofs_wait_obj_created (struct exofs_i_info*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_created (struct exofs_i_info*) ; 

__attribute__((used)) static inline int wait_obj_created(struct exofs_i_info *oi)
{
	if (likely(obj_created(oi)))
		return 0;

	return __exofs_wait_obj_created(oi);
}