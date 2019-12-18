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
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  dwBuildNumber; } ;
typedef  TYPE_1__ OSVERSIONINFOEXW ;

/* Variables and functions */
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_osbuildnumber( OSVERSIONINFOEXW *ver )
{
    static const WCHAR fmtW[] = {'%','u',0};
    WCHAR *ret = heap_alloc( 11 * sizeof(WCHAR) );
    if (ret) sprintfW( ret, fmtW, ver->dwBuildNumber );
    return ret;
}