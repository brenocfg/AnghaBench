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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetVolumeInformationW (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* heap_strdupW (char*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_volumeserialnumber( const WCHAR *root )
{
    static const WCHAR fmtW[] = {'%','0','8','X',0};
    DWORD serial = 0;
    WCHAR buffer[9];

    GetVolumeInformationW( root, NULL, 0, &serial, NULL, NULL, NULL, 0 );
    sprintfW( buffer, fmtW, serial );
    return heap_strdupW( buffer );
}