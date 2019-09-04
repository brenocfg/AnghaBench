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
typedef  int u32 ;
struct il_queue {int n_win; } ;

/* Variables and functions */

__attribute__((used)) static inline u8
il_get_cmd_idx(struct il_queue *q, u32 idx, int is_huge)
{
	/*
	 * This is for init calibration result and scan command which
	 * required buffer > TFD_MAX_PAYLOAD_SIZE,
	 * the big buffer at end of command array
	 */
	if (is_huge)
		return q->n_win;	/* must be power of 2 */

	/* Otherwise, use normal size buffers */
	return idx & (q->n_win - 1);
}