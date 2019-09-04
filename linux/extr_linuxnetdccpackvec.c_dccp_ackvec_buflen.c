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
typedef  int /*<<< orphan*/  u16 ;
struct dccp_ackvec {int /*<<< orphan*/  av_buf_head; int /*<<< orphan*/  av_buf_tail; int /*<<< orphan*/  av_overflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCPAV_MAX_ACKVEC_LEN ; 
 int /*<<< orphan*/  __ackvec_idx_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

u16 dccp_ackvec_buflen(const struct dccp_ackvec *av)
{
	if (unlikely(av->av_overflow))
		return DCCPAV_MAX_ACKVEC_LEN;
	return __ackvec_idx_sub(av->av_buf_tail, av->av_buf_head);
}