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
typedef  int u32 ;
struct cake_sched_data {int rate_flags; int max_netlen; int min_netlen; int rate_mpu; scalar_t__ atm_mode; int max_adjlen; int min_adjlen; scalar_t__ rate_overhead; } ;

/* Variables and functions */
 scalar_t__ CAKE_ATM_ATM ; 
 scalar_t__ CAKE_ATM_PTM ; 
 int CAKE_FLAG_OVERHEAD ; 

__attribute__((used)) static u32 cake_calc_overhead(struct cake_sched_data *q, u32 len, u32 off)
{
	if (q->rate_flags & CAKE_FLAG_OVERHEAD)
		len -= off;

	if (q->max_netlen < len)
		q->max_netlen = len;
	if (q->min_netlen > len)
		q->min_netlen = len;

	len += q->rate_overhead;

	if (len < q->rate_mpu)
		len = q->rate_mpu;

	if (q->atm_mode == CAKE_ATM_ATM) {
		len += 47;
		len /= 48;
		len *= 53;
	} else if (q->atm_mode == CAKE_ATM_PTM) {
		/* Add one byte per 64 bytes or part thereof.
		 * This is conservative and easier to calculate than the
		 * precise value.
		 */
		len += (len + 63) / 64;
	}

	if (q->max_adjlen < len)
		q->max_adjlen = len;
	if (q->min_adjlen > len)
		q->min_adjlen = len;

	return len;
}