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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetComputerNameW (int /*<<< orphan*/ *,int*) ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 

__attribute__((used)) static WCHAR *get_computername(void)
{
    WCHAR *ret;
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    if (!(ret = heap_alloc( size * sizeof(WCHAR) ))) return NULL;
    GetComputerNameW( ret, &size );
    return ret;
}