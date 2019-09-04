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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

int rtw_retrive_from_file(char *path, u8* buf, u32 sz)
{
#ifdef PLATFORM_LINUX
	int ret =retriveFromFile(path, buf, sz);
	return ret>=0?ret:0;
#else
	//Todo...
	return 0;
#endif
}