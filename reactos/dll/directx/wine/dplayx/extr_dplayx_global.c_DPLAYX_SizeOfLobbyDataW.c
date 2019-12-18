#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_15__ {scalar_t__ dwAddressSize; TYPE_6__* lpPlayerName; TYPE_3__* lpSessionDesc; } ;
struct TYPE_13__ {scalar_t__ lpszLongName; } ;
struct TYPE_12__ {scalar_t__ lpszShortName; } ;
struct TYPE_14__ {TYPE_5__ u2; TYPE_4__ u1; } ;
struct TYPE_10__ {scalar_t__ lpszPassword; } ;
struct TYPE_9__ {scalar_t__ lpszSessionName; } ;
struct TYPE_11__ {TYPE_2__ u2; TYPE_1__ u1; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DPSESSIONDESC2 ;
typedef  int /*<<< orphan*/  DPNAME ;
typedef  TYPE_7__ DPLCONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int lstrlenW (scalar_t__) ; 

__attribute__((used)) static DWORD DPLAYX_SizeOfLobbyDataW( const DPLCONNECTION *lpConn )
{
  DWORD dwTotalSize = sizeof( DPLCONNECTION );

  /* Just a safety check */
  if( lpConn == NULL )
  {
    ERR( "lpConn is NULL\n" );
    return 0;
  }

  if( lpConn->lpSessionDesc != NULL )
  {
    dwTotalSize += sizeof( DPSESSIONDESC2 );

    if( lpConn->lpSessionDesc->u1.lpszSessionName )
    {
      dwTotalSize += sizeof( WCHAR ) *
        ( lstrlenW( lpConn->lpSessionDesc->u1.lpszSessionName ) + 1 );
    }

    if( lpConn->lpSessionDesc->u2.lpszPassword )
    {
      dwTotalSize += sizeof( WCHAR ) *
        ( lstrlenW( lpConn->lpSessionDesc->u2.lpszPassword ) + 1 );
    }
  }

  if( lpConn->lpPlayerName != NULL )
  {
    dwTotalSize += sizeof( DPNAME );

    if( lpConn->lpPlayerName->u1.lpszShortName )
    {
      dwTotalSize += sizeof( WCHAR ) *
        ( lstrlenW( lpConn->lpPlayerName->u1.lpszShortName ) + 1 );
    }

    if( lpConn->lpPlayerName->u2.lpszLongName )
    {
      dwTotalSize += sizeof( WCHAR ) *
        ( lstrlenW( lpConn->lpPlayerName->u2.lpszLongName ) + 1 );
    }

  }

  dwTotalSize += lpConn->dwAddressSize;

  return dwTotalSize;
}