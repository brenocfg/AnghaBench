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
struct dccp_ackvec {scalar_t__ av_overflow; scalar_t__ av_buf_head; scalar_t__ av_buf_tail; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dccp_ackvec_is_empty(const struct dccp_ackvec *av)
{
	return av->av_overflow == 0 && av->av_buf_head == av->av_buf_tail;
}