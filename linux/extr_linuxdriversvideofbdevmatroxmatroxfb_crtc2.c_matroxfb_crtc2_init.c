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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  crtc2 ; 
 scalar_t__ fb_get_options (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matroxfb_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int matroxfb_crtc2_init(void) {
	if (fb_get_options("matrox_crtc2fb", NULL))
		return -ENODEV;

	matroxfb_register_driver(&crtc2);
	return 0;
}