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

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 

void PrintUsage()
{
    _tprintf( _T("Usage:\n"
                 "   nslookup [-opt ...]             # interactive mode using"
                 " default server\n   nslookup [-opt ...] - server    #"
                 " interactive mode using 'server'\n   nslookup [-opt ...]"
                 " host        # just look up 'host' using default server\n"
                 "   nslookup [-opt ...] host server # just look up 'host'"
                 " using 'server'\n") );
}