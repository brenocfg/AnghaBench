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
struct qm_eqcr_entry {int dummy; } ;

/* Variables and functions */
 uintptr_t EQCR_SHIFT ; 
 int QM_EQCR_SIZE ; 

__attribute__((used)) static int eqcr_ptr2idx(struct qm_eqcr_entry *e)
{
	return ((uintptr_t)e >> EQCR_SHIFT) & (QM_EQCR_SIZE - 1);
}