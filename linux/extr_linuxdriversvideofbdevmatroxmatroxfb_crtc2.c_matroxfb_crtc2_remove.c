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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  matroxfb_dh_deregisterfb (void*) ; 

__attribute__((used)) static void matroxfb_crtc2_remove(struct matrox_fb_info* minfo, void* crtc2) {
	matroxfb_dh_deregisterfb(crtc2);
	kfree(crtc2);
}