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
typedef  int u64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int prandom_u32 () ; 

__attribute__((used)) static inline s32 rfc3315_s14_backoff_init(s32 irt)
{
	/* multiply 'initial retransmission time' by 0.9 .. 1.1 */
	u64 tmp = (900000 + prandom_u32() % 200001) * (u64)irt;
	do_div(tmp, 1000000);
	return (s32)tmp;
}