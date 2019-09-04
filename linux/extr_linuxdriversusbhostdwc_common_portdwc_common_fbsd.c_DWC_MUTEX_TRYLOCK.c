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
 int mtx_trylock (struct mtx*) ; 

int DWC_MUTEX_TRYLOCK(dwc_mutex_t *mutex)
{
	struct mtx *m = (struct mtx *)mutex;

	return mtx_trylock(m);
}