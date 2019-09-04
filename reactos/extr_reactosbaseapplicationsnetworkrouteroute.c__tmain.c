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
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 int PrintRoutes () ; 
 int Usage () ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int add_route (int,int /*<<< orphan*/ **) ; 
 int del_route (int,int /*<<< orphan*/ **) ; 

int _tmain( int argc, TCHAR **argv )
{
    if( argc < 2 )
        return Usage();
    else if ( !_tcscmp( argv[1], _T("print") ) )
        return PrintRoutes();
    else if( !_tcscmp( argv[1], _T("add") ) )
        return add_route( argc-2, argv+2 );
    else if( !_tcscmp( argv[1], _T("delete") ) )
        return del_route( argc-2, argv+2 );
    else
        return Usage();
}