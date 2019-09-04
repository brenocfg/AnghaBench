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

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int chomp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_args( WCHAR *cmdline, int *pargc, WCHAR ***pargv )
{
    WCHAR **argv, *p;
    int i, count;

    *pargc = 0;
    *pargv = NULL;

    count = chomp( cmdline, NULL );
    if (!(p = HeapAlloc( GetProcessHeap(), 0, (lstrlenW(cmdline) + count + 1) * sizeof(WCHAR) )))
        return;

    count = chomp( cmdline, p );
    if (!(argv = HeapAlloc( GetProcessHeap(), 0, (count + 1) * sizeof(WCHAR *) )))
    {
        HeapFree( GetProcessHeap(), 0, p );
        return;
    }
    for (i = 0; i < count; i++)
    {
        argv[i] = p;
        p += lstrlenW( p ) + 1;
    }
    argv[i] = NULL;

    *pargc = count;
    *pargv = argv;
}