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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  op_table_entry ;

/* Variables and functions */
 int /*<<< orphan*/  const* g_op_table ; 
 size_t g_op_table_size ; 

__attribute__((used)) static const op_table_entry* op_table_find(uint32_t op)
{
    return op >= g_op_table_size ? NULL : &g_op_table[op];
}