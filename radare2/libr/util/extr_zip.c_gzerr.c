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

__attribute__((used)) static const char *gzerr(int n) {
	const char *errors[] = {
		"",
		"file error",          /* Z_ERRNO         (-1) */
		"stream error",        /* Z_STREAM_ERROR  (-2) */
		"data error",          /* Z_DATA_ERROR    (-3) */
		"insufficient memory", /* Z_MEM_ERROR     (-4) */
		"buffer error",        /* Z_BUF_ERROR     (-5) */
		"incompatible version",/* Z_VERSION_ERROR (-6) */
	};
	if (n<1 || n>6) {
		return "unknown";
	}
	return errors[n];
}