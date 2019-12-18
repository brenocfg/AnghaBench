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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int ERROR_ALREADY_EXISTS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 scalar_t__* PathFindFileNameW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PathIsDirectoryW (int /*<<< orphan*/ *) ; 
 int SHCreateDirectoryExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINE_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_target_directory(LPWSTR Target)
{
    WCHAR dir[MAX_PATH];
    int res;

    strcpyW(dir, Target);
    *PathFindFileNameW(dir) = 0; /* Truncate file name */
    if(!PathIsDirectoryW(dir))
    {
        res = SHCreateDirectoryExW(NULL, dir, NULL);
        if(res != ERROR_SUCCESS && res != ERROR_ALREADY_EXISTS)
            WINE_ERR("Can't create directory: %s\n", wine_dbgstr_w(dir));
    }
}