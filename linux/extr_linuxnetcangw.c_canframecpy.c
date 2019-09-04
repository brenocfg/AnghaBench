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
typedef  int /*<<< orphan*/  u64 ;
struct can_frame {scalar_t__ data; int /*<<< orphan*/  can_dlc; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */

__attribute__((used)) static inline void canframecpy(struct can_frame *dst, struct can_frame *src)
{
	/*
	 * Copy the struct members separately to ensure that no uninitialized
	 * data are copied in the 3 bytes hole of the struct. This is needed
	 * to make easy compares of the data in the struct cf_mod.
	 */

	dst->can_id = src->can_id;
	dst->can_dlc = src->can_dlc;
	*(u64 *)dst->data = *(u64 *)src->data;
}