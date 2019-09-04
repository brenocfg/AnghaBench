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
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_FREE (struct mtx*) ; 
 int /*<<< orphan*/  mtx_destroy (struct mtx*) ; 

void DWC_SPINLOCK_FREE(dwc_spinlock_t *lock)
{
	struct mtx *sl = (struct mtx *)lock;

	mtx_destroy(sl);
	DWC_FREE(sl);
}