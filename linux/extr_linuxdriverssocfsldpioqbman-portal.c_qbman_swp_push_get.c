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
typedef  int u16 ;
struct qbman_swp {int sdq; } ;

/* Variables and functions */
 int QB_SDQCR_SRC_MASK ; 
 int QB_SDQCR_SRC_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void qbman_swp_push_get(struct qbman_swp *s, u8 channel_idx, int *enabled)
{
	u16 src = (s->sdq >> QB_SDQCR_SRC_SHIFT) & QB_SDQCR_SRC_MASK;

	WARN_ON(channel_idx > 15);
	*enabled = src | (1 << channel_idx);
}