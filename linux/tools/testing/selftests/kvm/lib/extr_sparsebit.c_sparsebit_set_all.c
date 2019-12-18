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
struct sparsebit {int dummy; } ;
typedef  int /*<<< orphan*/  sparsebit_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparsebit_all_set (struct sparsebit*) ; 
 int /*<<< orphan*/  sparsebit_set (struct sparsebit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparsebit_set_num (struct sparsebit*,int,int /*<<< orphan*/ ) ; 

void sparsebit_set_all(struct sparsebit *s)
{
	sparsebit_set(s, 0);
	sparsebit_set_num(s, 1, ~(sparsebit_idx_t) 0);
	assert(sparsebit_all_set(s));
}