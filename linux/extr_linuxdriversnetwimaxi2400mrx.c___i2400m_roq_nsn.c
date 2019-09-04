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
struct i2400m_roq {scalar_t__ ws; } ;

/* Variables and functions */

__attribute__((used)) static
unsigned __i2400m_roq_nsn(struct i2400m_roq *roq, unsigned sn)
{
	int r;
	r =  ((int) sn - (int) roq->ws) % 2048;
	if (r < 0)
		r += 2048;
	return r;
}