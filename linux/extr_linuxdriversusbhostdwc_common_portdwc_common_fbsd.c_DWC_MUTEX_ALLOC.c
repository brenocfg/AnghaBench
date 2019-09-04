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
typedef  int /*<<< orphan*/  dwc_mutex_t ;

/* Variables and functions */
 scalar_t__ DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  mtx_init (struct mtx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

dwc_mutex_t *DWC_MUTEX_ALLOC(void)
{
	struct mtx *m;
	dwc_mutex_t *mutex = (dwc_mutex_t *)DWC_ALLOC(sizeof(struct mtx));

	if (!mutex) {
		DWC_ERROR("Cannot allocate memory for mutex");
		return NULL;
	}

	m = (struct mtx *)mutex;
	mtx_init(m, "dw3mtx", NULL, MTX_DEF);
	return mutex;
}