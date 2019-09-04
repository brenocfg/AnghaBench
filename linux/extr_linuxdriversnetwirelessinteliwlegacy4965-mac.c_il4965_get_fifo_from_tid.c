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
typedef  int u8 ;
typedef  size_t u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int EINVAL ; 
#define  IL_TX_FIFO_BE 131 
#define  IL_TX_FIFO_BK 130 
#define  IL_TX_FIFO_VI 129 
#define  IL_TX_FIFO_VO 128 
 scalar_t__ likely (int) ; 
 size_t* tid_to_ac ; 

__attribute__((used)) static inline int
il4965_get_fifo_from_tid(u16 tid)
{
	static const u8 ac_to_fifo[] = {
		IL_TX_FIFO_VO,
		IL_TX_FIFO_VI,
		IL_TX_FIFO_BE,
		IL_TX_FIFO_BK,
	};

	if (likely(tid < ARRAY_SIZE(tid_to_ac)))
		return ac_to_fifo[tid_to_ac[tid]];

	/* no support for TIDs 8-15 yet */
	return -EINVAL;
}