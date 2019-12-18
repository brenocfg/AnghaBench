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
 scalar_t__ astrcmpi (char const*,char*) ; 

__attribute__((used)) static bool valid_extension(const char *ext)
{
	if (!ext)
		return false;
	return astrcmpi(ext, ".bmp") == 0 || astrcmpi(ext, ".tga") == 0 ||
	       astrcmpi(ext, ".png") == 0 || astrcmpi(ext, ".jpeg") == 0 ||
	       astrcmpi(ext, ".jpg") == 0 || astrcmpi(ext, ".gif") == 0;
}