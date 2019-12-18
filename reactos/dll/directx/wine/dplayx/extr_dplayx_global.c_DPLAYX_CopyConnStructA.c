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
struct TYPE_17__ {int /*<<< orphan*/  dwAddressSize; int /*<<< orphan*/ * lpAddress; TYPE_6__* lpPlayerName; TYPE_5__* lpSessionDesc; } ;
struct TYPE_14__ {void* lpszLongNameA; scalar_t__ lpszLongName; } ;
struct TYPE_13__ {void* lpszShortNameA; } ;
struct TYPE_16__ {TYPE_4__ u2; TYPE_3__ u1; } ;
struct TYPE_12__ {void* lpszPasswordA; } ;
struct TYPE_11__ {void* lpszSessionNameA; } ;
struct TYPE_15__ {TYPE_2__ u2; TYPE_1__ u1; } ;
typedef  void* LPSTR ;
typedef  TYPE_5__* LPDPSESSIONDESC2 ;
typedef  TYPE_6__* LPDPNAME ;
typedef  TYPE_7__* LPDPLCONNECTION ;
typedef  int /*<<< orphan*/  DPSESSIONDESC2 ;
typedef  int /*<<< orphan*/  DPNAME ;
typedef  TYPE_7__ DPLCONNECTION ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (void*,void*) ; 
 scalar_t__ strlen (void*) ; 

__attribute__((used)) static void DPLAYX_CopyConnStructA( LPDPLCONNECTION dest, const DPLCONNECTION *src )
{
  BYTE* lpStartOfFreeSpace;

  *dest = *src;

  lpStartOfFreeSpace = ((BYTE*)dest) + sizeof( DPLCONNECTION );

  /* Copy the LPDPSESSIONDESC2 structure if it exists */
  if( src->lpSessionDesc )
  {
    dest->lpSessionDesc = (LPDPSESSIONDESC2)lpStartOfFreeSpace;
    lpStartOfFreeSpace += sizeof( DPSESSIONDESC2 );
    *dest->lpSessionDesc = *src->lpSessionDesc;

    /* Session names may or may not exist */
    if( src->lpSessionDesc->u1.lpszSessionNameA )
    {
      strcpy( (LPSTR)lpStartOfFreeSpace, src->lpSessionDesc->u1.lpszSessionNameA );
      dest->lpSessionDesc->u1.lpszSessionNameA = (LPSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=
        strlen( dest->lpSessionDesc->u1.lpszSessionNameA ) + 1;
    }

    if( src->lpSessionDesc->u2.lpszPasswordA )
    {
      strcpy( (LPSTR)lpStartOfFreeSpace, src->lpSessionDesc->u2.lpszPasswordA );
      dest->lpSessionDesc->u2.lpszPasswordA = (LPSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=
        strlen( dest->lpSessionDesc->u2.lpszPasswordA ) + 1;
    }
  }

  /* DPNAME structure is optional */
  if( src->lpPlayerName )
  {
    dest->lpPlayerName = (LPDPNAME)lpStartOfFreeSpace;
    lpStartOfFreeSpace += sizeof( DPNAME );
    *dest->lpPlayerName = *src->lpPlayerName;

    if( src->lpPlayerName->u1.lpszShortNameA )
    {
      strcpy( (LPSTR)lpStartOfFreeSpace, src->lpPlayerName->u1.lpszShortNameA );
      dest->lpPlayerName->u1.lpszShortNameA = (LPSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=
        strlen( dest->lpPlayerName->u1.lpszShortNameA ) + 1;
    }

    if( src->lpPlayerName->u2.lpszLongNameA )
    {
      strcpy( (LPSTR)lpStartOfFreeSpace, src->lpPlayerName->u2.lpszLongNameA );
      dest->lpPlayerName->u2.lpszLongNameA = (LPSTR)lpStartOfFreeSpace;
      lpStartOfFreeSpace +=
        strlen( (LPSTR)dest->lpPlayerName->u2.lpszLongName ) + 1 ;
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