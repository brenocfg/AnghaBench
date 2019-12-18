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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  fi ;
struct TYPE_3__ {int dwAttributes; } ;
typedef  TYPE_1__ SHFILEINFO ;

/* Variables and functions */
 int /*<<< orphan*/  Cwd ; 
 int /*<<< orphan*/  ENOENT ; 
 int SFGAO_FOLDER ; 
 int /*<<< orphan*/  SHGFI_ATTRIBUTES ; 
 int /*<<< orphan*/  SHGetFileInfo (scalar_t__ const*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,scalar_t__ const*) ; 

int wceex_wchdir( const wchar_t *dirname )
{
    if( !dirname || *dirname == 0 )
    {
        errno = ENOENT;
        return -1;
    }
    else
    {
        SHFILEINFO fi;
        if( !SHGetFileInfo( dirname, 0, &fi, sizeof(fi), SHGFI_ATTRIBUTES ) )
        {
            errno = ENOENT;
            return -1;
        }
        if( !(fi.dwAttributes & SFGAO_FOLDER) )
        {
            errno = ENOENT;
            return -1;
        }
        wcscpy( Cwd, dirname );
        return 0;
    }
}