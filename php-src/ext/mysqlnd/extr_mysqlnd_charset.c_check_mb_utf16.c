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
 scalar_t__ UTF16_HIGH_HEAD (char const) ; 
 scalar_t__ UTF16_LOW_HEAD (char const) ; 

__attribute__((used)) static unsigned int check_mb_utf16(const char * const start, const char * const end)
{
	if (start + 2 > end) {
		return 0;
	}

	if (UTF16_HIGH_HEAD(*start)) {
		return (start + 4 <= end) && UTF16_LOW_HEAD(start[2]) ? 4 : 0;
	}

	if (UTF16_LOW_HEAD(*start)) {
		return 0;
	}
	return 2;
}