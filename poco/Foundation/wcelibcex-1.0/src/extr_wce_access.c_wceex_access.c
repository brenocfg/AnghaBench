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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int _MAX_PATH ; 
 int /*<<< orphan*/  errno ; 
 int wceex_waccess (int /*<<< orphan*/ *,int) ; 

int wceex_access( const char *path, int mode )
{
    wchar_t wpath[_MAX_PATH];
	if( !MultiByteToWideChar( CP_ACP, 0, path, -1, wpath, _MAX_PATH ) )
    {
        errno = ENOENT;
        return -1;
    }
    return wceex_waccess( wpath, mode );
}