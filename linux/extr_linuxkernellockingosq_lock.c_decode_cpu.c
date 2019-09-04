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
struct optimistic_spin_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  osq_node ; 
 struct optimistic_spin_node* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct optimistic_spin_node *decode_cpu(int encoded_cpu_val)
{
	int cpu_nr = encoded_cpu_val - 1;

	return per_cpu_ptr(&osq_node, cpu_nr);
}