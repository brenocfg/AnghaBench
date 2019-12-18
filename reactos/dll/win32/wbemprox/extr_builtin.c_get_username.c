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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetComputerNameW (char*,int*) ; 
 int /*<<< orphan*/  GetUserNameW (char*,int*) ; 
 char* heap_alloc (int) ; 

__attribute__((used)) static WCHAR *get_username(void)
{
    WCHAR *ret;
    DWORD compsize, usersize;
    DWORD size;

    compsize = 0;
    GetComputerNameW( NULL, &compsize );
    usersize = 0;
    GetUserNameW( NULL, &usersize );
    size = compsize + usersize; /* two null terminators account for the \ */
    if (!(ret = heap_alloc( size * sizeof(WCHAR) ))) return NULL;
    GetComputerNameW( ret, &compsize );
    ret[compsize] = '\\';
    GetUserNameW( ret + compsize + 1, &usersize );
    return ret;
}