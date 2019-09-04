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
struct whc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asl_start (struct whc*) ; 
 int /*<<< orphan*/  pzl_start (struct whc*) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

int whc_wusbhc_start(struct wusbhc *wusbhc)
{
	struct whc *whc = wusbhc_to_whc(wusbhc);

	asl_start(whc);
	pzl_start(whc);

	return 0;
}