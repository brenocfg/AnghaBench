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
struct inet_diag_markcond {int dummy; } ;
struct inet_diag_bc_op {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool valid_markcond(const struct inet_diag_bc_op *op, int len,
			   int *min_len)
{
	*min_len += sizeof(struct inet_diag_markcond);
	return len >= *min_len;
}