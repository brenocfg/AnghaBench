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
struct xfs_perag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_ag_measure_sickness (struct xfs_perag*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static inline bool
xfs_ag_has_sickness(struct xfs_perag *pag, unsigned int mask)
{
	unsigned int	sick, checked;

	xfs_ag_measure_sickness(pag, &sick, &checked);
	return sick & mask;
}