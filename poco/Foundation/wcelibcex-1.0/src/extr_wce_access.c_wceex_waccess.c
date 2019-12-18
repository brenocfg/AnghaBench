#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  fi ;
struct TYPE_3__ {int dwAttributes; } ;
typedef  TYPE_1__ SHFILEINFO ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOENT ; 
 int SFGAO_READONLY ; 
 int /*<<< orphan*/  SHGFI_ATTRIBUTES ; 
 int /*<<< orphan*/  SHGetFileInfo (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int wceex_waccess( const wchar_t *path, int mode )
{
    SHFILEINFO fi;
    if( !SHGetFileInfo( path, 0, &fi, sizeof(fi), SHGFI_ATTRIBUTES ) )
    {
        errno = ENOENT;
        return -1;
    }
    // existence ?
    if( mode == 0 )
        return 0;
    // write permission ?
    if( mode & 2 )
    {
        if( fi.dwAttributes & SFGAO_READONLY )
        {
            errno = EACCES;
            return -1;
        }
    }
    return 0;
}