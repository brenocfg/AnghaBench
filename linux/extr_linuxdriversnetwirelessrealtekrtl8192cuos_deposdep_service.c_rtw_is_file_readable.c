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
 int _FALSE ; 

int rtw_is_file_readable(char *path)
{
#ifdef PLATFORM_LINUX
	if(isFileReadable(path) == 0)
		return _TRUE;
	else
		return _FALSE;
#else
	//Todo...
	return _FALSE;
#endif
}