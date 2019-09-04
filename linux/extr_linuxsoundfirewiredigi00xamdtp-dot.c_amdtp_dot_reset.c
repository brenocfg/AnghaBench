#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amdtp_stream {struct amdtp_dot* protocol; } ;
struct TYPE_2__ {int carry; int idx; scalar_t__ off; } ;
struct amdtp_dot {TYPE_1__ state; } ;

/* Variables and functions */

void amdtp_dot_reset(struct amdtp_stream *s)
{
	struct amdtp_dot *p = s->protocol;

	p->state.carry = 0x00;
	p->state.idx = 0x00;
	p->state.off = 0;
}