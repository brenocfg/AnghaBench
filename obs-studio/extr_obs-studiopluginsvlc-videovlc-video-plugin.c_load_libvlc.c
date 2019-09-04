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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ libvlc ; 
 scalar_t__ libvlc_clock_ () ; 
 scalar_t__ libvlc_new_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long time_start ; 

bool load_libvlc(void)
{
	if (libvlc)
		return true;

	libvlc = libvlc_new_(0, 0);
	if (!libvlc) {
		blog(LOG_INFO, "Couldn't create libvlc instance");
		return false;
	}

	time_start = (uint64_t)libvlc_clock_() * 1000ULL;
	return true;
}