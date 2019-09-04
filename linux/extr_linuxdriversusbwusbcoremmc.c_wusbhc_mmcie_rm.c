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
struct wusbhc {unsigned int mmcies_max; int (* mmcie_rm ) (struct wusbhc*,unsigned int) ;int /*<<< orphan*/  mmcie_mutex; struct wuie_hdr** mmcie; } ;
struct wuie_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wusbhc*,unsigned int) ; 

void wusbhc_mmcie_rm(struct wusbhc *wusbhc, struct wuie_hdr *wuie)
{
	int result;
	unsigned handle, itr;

	mutex_lock(&wusbhc->mmcie_mutex);
	for (itr = 0; itr < wusbhc->mmcies_max; itr++) {
		if (wusbhc->mmcie[itr] == wuie) {
			handle = itr;
			goto found;
		}
	}
	mutex_unlock(&wusbhc->mmcie_mutex);
	return;

found:
	result = (wusbhc->mmcie_rm)(wusbhc, handle);
	if (result == 0)
		wusbhc->mmcie[itr] = NULL;
	mutex_unlock(&wusbhc->mmcie_mutex);
}