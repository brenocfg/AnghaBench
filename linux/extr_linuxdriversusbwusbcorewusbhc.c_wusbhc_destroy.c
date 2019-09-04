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
struct wusbhc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wusbhc_devconnect_destroy (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_mmcie_destroy (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_rh_destroy (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_sec_destroy (struct wusbhc*) ; 

void wusbhc_destroy(struct wusbhc *wusbhc)
{
	wusbhc_sec_destroy(wusbhc);
	wusbhc_rh_destroy(wusbhc);
	wusbhc_devconnect_destroy(wusbhc);
	wusbhc_mmcie_destroy(wusbhc);
}