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
struct orangefs_kernel_op_s {int /*<<< orphan*/  slot_to_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  op_release (struct orangefs_kernel_op_s*) ; 
 int /*<<< orphan*/  orangefs_bufmap_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void put_cancel(struct orangefs_kernel_op_s *op)
{
	orangefs_bufmap_put(op->slot_to_free);
	op_release(op);
}