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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct illinois {scalar_t__ base_rtt; int /*<<< orphan*/  cnt_rtt; scalar_t__ sum_rtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 avg_delay(const struct illinois *ca)
{
	u64 t = ca->sum_rtt;

	do_div(t, ca->cnt_rtt);
	return t - ca->base_rtt;
}