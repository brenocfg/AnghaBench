#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_17__ {int /*<<< orphan*/  dwAddressSize; int /*<<< orphan*/ * lpAddress; TYPE_6__* lpPlayerName; TYPE_5__* lpSessionDesc; } ;
struct TYPE_14__ {void* lpszLongName; } ;
struct TYPE_13__ {void* lpszShortName; } ;
struct TYPE_16__ {TYPE_4__ u2; TYPE_3__ u1; } ;
struct TYPE_12__ {void* lpszPassword; } ;
struct TYPE_11__ {void* lpszSessionName; } ;
struct TYPE_15__ {TYPE_2__ u2; TYPE_1__ u1; } ;
typedef  void* LPWSTR ;
typedef  TYPE_5__* LPDPSESSIONDESC2 ;
typedef  TYPE_6__* LPDPNAME ;
typedef  TYPE_7__* LPDPLCONNECTION ;
typedef  int /*<<< orphan*/  DPSESSIONDESC2 ;
typedef  int /*<<< orphan*/  DPNAME ;
typedef  TYPE_7__ DPLCONNECTION ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (void*,void*) ; 
 int lstrlenW (void*) ; 

__attribute__((used)) static void DPLAYX_CopyConnStructW( LPDPLCONNECTION dest, const DPLCONNECTION *src )
{
  BYTE*              lpStartOfFreeSpace;

  *dest = *src;

  lpStartOfFreeSpace = ( (BYTE*)dest) + sizeof( DPLCONNECTION );

  /* Copy the LPDPSESSIONDESC2 structure if it exists */
  if( src->lpSessionDesc )
  {
    dest->lpSessionDesc = (LPDPSESSIONDESC2)lpStartOfFreeSpace;
    lpStartOfFreeSpace += sizeof( DPSESSIONDESC2 );
    *dest->lpSessionDesc = *src->lpSessionDesc;

    /* Session names may or may not exist */
    if( src->lpSessionDesc->u1.lpszSessionName )
    {
      lstrcpyW( (LPWSTR)lpStartOfFreeSpace, src->lpSessionDesc->u1.lpszSessionName );
      dest->lpSessionDesc->u1.lpszSessionName = (LPWSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=  sizeof(WCHAR) *
        ( lstrlenW( dest->lpSessionDesc->u1.lpszSessionName ) + 1 );
    }

    if( src->lpSessionDesc->u2.lpszPassword )
    {
      lstrcpyW( (LPWSTR)lpStartOfFreeSpace, src->lpSessionDesc->u2.lpszPassword );
      dest->lpSessionDesc->u2.lpszPassword = (LPWSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=  sizeof(WCHAR) *
        ( lstrlenW( dest->lpSessionDesc->u2.lpszPassword ) + 1 );
    }
  }

  /* DPNAME structure is optional */
  if( src->lpPlayerName )
  {
    dest->lpPlayerName = (LPDPNAME)lpStartOfFreeSpace;
    lpStartOfFreeSpace += sizeof( DPNAME );
    *dest->lpPlayerName = *src->lpPlayerName;

    if( src->lpPlayerName->u1.lpszShortName )
    {
      lstrcpyW( (LPWSTR)lpStartOfFreeSpace, src->lpPlayerName->u1.lpszShortName );
      dest->lpPlayerName->u1.lpszShortName = (LPWSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=  sizeof(WCHAR) *
        ( lstrlenW( dest->lpPlayerName->u1.lpszShortName ) + 1 );
    }

    if( src->lpPlayerName->u2.lpszLongName )
    {
      lstrcpyW( (LPWSTR)lpStartOfFreeSpace, src->lpPlayerName->u2.lpszLongName );
      dest->lpPlayerName->u2.lpszLongName = (LPWSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=  sizeof(WCHAR) *
        ( lstrlenW( dest->lpPlayerName->u2.lpszLongName ) + 1 );
    }

  }

  /* Copy address if it exists */
  if( src->lpAddress )
  {
    dest->lpAddress = lpStartOfFreeSpace;
    CopyMemory( lpStartOfFreeSpace, src->lpAddress, src->dwAddressSize );
    /* No need to advance lpStartOfFreeSpace as there is no more "dynamic" data */
  }

}