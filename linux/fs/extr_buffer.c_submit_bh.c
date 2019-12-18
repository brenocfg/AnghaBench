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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int submit_bh_wbc (int,int,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int submit_bh(int op, int op_flags, struct buffer_head *bh)
{
	return submit_bh_wbc(op, op_flags, bh, 0, NULL);
}