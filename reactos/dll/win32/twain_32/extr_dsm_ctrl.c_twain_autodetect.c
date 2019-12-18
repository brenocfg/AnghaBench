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
 scalar_t__ TRUE ; 
 scalar_t__ detectionrun ; 
 int /*<<< orphan*/  twain_add_onedriver (char*) ; 

__attribute__((used)) static void
twain_autodetect(void) {
	if (detectionrun) return;
        detectionrun = TRUE;

	twain_add_onedriver("sane.ds");
	twain_add_onedriver("gphoto2.ds");
#if 0
	twain_add_onedriver("c:\\windows\\Twain_32\\Largan\\sp503a.ds");
	twain_add_onedriver("c:\\windows\\Twain_32\\vivicam10\\vivicam10.ds");
	twain_add_onedriver("c:\\windows\\Twain_32\\ws30slim\\sp500a.ds");
#endif
}