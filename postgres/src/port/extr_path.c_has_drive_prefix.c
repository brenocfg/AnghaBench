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
 char const* skip_drive (char const*) ; 

bool
has_drive_prefix(const char *path)
{
#ifdef WIN32
	return skip_drive(path) != path;
#else
	return false;
#endif
}