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
struct orangefs_kernel_op_s {int /*<<< orphan*/  list; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int hash_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_table_size ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * orangefs_htable_ops_in_progress ; 

__attribute__((used)) static void orangefs_devreq_add_op(struct orangefs_kernel_op_s *op)
{
	int index = hash_func(op->tag, hash_table_size);

	list_add_tail(&op->list, &orangefs_htable_ops_in_progress[index]);
}