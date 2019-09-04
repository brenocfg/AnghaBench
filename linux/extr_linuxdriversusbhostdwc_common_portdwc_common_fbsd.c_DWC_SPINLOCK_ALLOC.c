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
 struct mtx* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  mtx_init (struct mtx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

dwc_spinlock_t *DWC_SPINLOCK_ALLOC(void)
{
	struct mtx *sl = DWC_ALLOC(sizeof(*sl));

	if (!sl) {
		DWC_ERROR("Cannot allocate memory for spinlock");
		return NULL;
	}

	mtx_init(sl, "dw3spn", NULL, MTX_SPIN);
	return (dwc_spinlock_t *)sl;
}