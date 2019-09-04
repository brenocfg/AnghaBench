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
struct TYPE_2__ {int port; int type; int Class; int root; int domain; int* srchlist; scalar_t__ ixfrver; int /*<<< orphan*/  MSxfr; scalar_t__ retry; scalar_t__ timeout; int /*<<< orphan*/  ignoretc; int /*<<< orphan*/  vc; int /*<<< orphan*/  d2; int /*<<< orphan*/  recurse; int /*<<< orphan*/  search; int /*<<< orphan*/  defname; int /*<<< orphan*/  debug; } ;

/* Variables and functions */
 TYPE_1__ State ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

void PrintState()
{
    _tprintf( _T("Default Server:  (null)\n\n") );
    _tprintf( _T("Set options:\n") );

    _tprintf( _T("  ") );
    if( !State.debug ) _tprintf( _T("no") );
    _tprintf( _T("debug\n") );

    _tprintf( _T("  ") );
    if( !State.defname ) _tprintf( _T("no") );
    _tprintf( _T("defname\n") );

    _tprintf( _T("  ") );
    if( !State.search ) _tprintf( _T("no") );
    _tprintf( _T("search\n") );

    _tprintf( _T("  ") );
    if( !State.recurse ) _tprintf( _T("no") );
    _tprintf( _T("recurse\n") );

    _tprintf( _T("  ") );
    if( !State.d2 ) _tprintf( _T("no") );
    _tprintf( _T("d2\n") );

    _tprintf( _T("  ") );
    if( !State.vc ) _tprintf( _T("no") );
    _tprintf( _T("vc\n") );

    _tprintf( _T("  ") );
    if( !State.ignoretc ) _tprintf( _T("no") );
    _tprintf( _T("ignoretc\n") );

    _tprintf( _T("  port=%d\n"), State.port );
    _tprintf( _T("  type=%s\n"), State.type );
    _tprintf( _T("  class=%s\n"), State.Class );
    _tprintf( _T("  timeout=%d\n"), (int)State.timeout );
    _tprintf( _T("  retry=%d\n"), (int)State.retry );
    _tprintf( _T("  root=%s\n"), State.root );
    _tprintf( _T("  domain=%s\n"), State.domain );

    _tprintf( _T("  ") );
    if( !State.MSxfr ) _tprintf( _T("no") );
    _tprintf( _T("MSxfr\n") );

    _tprintf( _T("  IXFRversion=%d\n"), (int)State.ixfrver );

    _tprintf( _T("  srchlist=%s\n\n"), State.srchlist[0] );
}