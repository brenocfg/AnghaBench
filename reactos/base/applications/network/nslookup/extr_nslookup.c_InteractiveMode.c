#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  DefaultServerAddress; int /*<<< orphan*/  DefaultServer; } ;

/* Variables and functions */
 TYPE_1__ State ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

void InteractiveMode()
{
    _tprintf( _T("Default Server:  %s\n"), State.DefaultServer );
    _tprintf( _T("Address:  %s\n\n"), State.DefaultServerAddress );

    /* TODO: Implement interactive mode. */

    _tprintf( _T("ERROR: Feature not implemented.\n") );
}