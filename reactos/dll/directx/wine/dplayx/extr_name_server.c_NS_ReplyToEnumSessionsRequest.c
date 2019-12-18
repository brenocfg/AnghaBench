#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  lpszSessionNameA; } ;
struct TYPE_15__ {TYPE_3__ u1; int /*<<< orphan*/  dwSize; } ;
struct TYPE_14__ {TYPE_4__* dp2; } ;
struct TYPE_10__ {int /*<<< orphan*/  wVersion; int /*<<< orphan*/  wCommandId; int /*<<< orphan*/  dwMagic; } ;
struct TYPE_13__ {int dwUnknown; int /*<<< orphan*/  sd; TYPE_2__ envelope; } ;
struct TYPE_9__ {int dwSPHeaderSize; } ;
struct TYPE_12__ {TYPE_8__* lpSessionDesc; TYPE_1__ spData; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_5__* LPDPMSG_ENUMSESSIONSREPLY ;
typedef  TYPE_6__ IDirectPlayImpl ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPMSGCMD_ENUMSESSIONSREPLY ; 
 int /*<<< orphan*/  DPMSGMAGIC_DPLAYMSG ; 
 int /*<<< orphan*/  DPMSGVER_DP6 ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

void NS_ReplyToEnumSessionsRequest( const void *lpcMsg, void **lplpReplyData, DWORD *lpdwReplySize,
        IDirectPlayImpl *lpDP )
{
  LPDPMSG_ENUMSESSIONSREPLY rmsg;
  DWORD dwVariableSize;
  DWORD dwVariableLen;
  /* LPCDPMSG_ENUMSESSIONSREQUEST msg = (LPDPMSG_ENUMSESSIONSREQUEST)lpcMsg; */

  /* FIXME: Should handle ANSI or WIDECHAR input. Currently just ANSI input */
  FIXME( ": few fixed + need to check request for response, might need UNICODE input ability.\n" );

  dwVariableLen = MultiByteToWideChar( CP_ACP, 0,
                                       lpDP->dp2->lpSessionDesc->u1.lpszSessionNameA,
                                       -1, NULL, 0 );
  dwVariableSize = dwVariableLen * sizeof( WCHAR );

  *lpdwReplySize = lpDP->dp2->spData.dwSPHeaderSize +
                     sizeof( *rmsg ) + dwVariableSize;
  *lplpReplyData = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                              *lpdwReplySize );

  rmsg = (LPDPMSG_ENUMSESSIONSREPLY)( (BYTE*)*lplpReplyData +
                                             lpDP->dp2->spData.dwSPHeaderSize);

  rmsg->envelope.dwMagic    = DPMSGMAGIC_DPLAYMSG;
  rmsg->envelope.wCommandId = DPMSGCMD_ENUMSESSIONSREPLY;
  rmsg->envelope.wVersion   = DPMSGVER_DP6;

  CopyMemory( &rmsg->sd, lpDP->dp2->lpSessionDesc,
              lpDP->dp2->lpSessionDesc->dwSize );
  rmsg->dwUnknown = 0x0000005c;
  MultiByteToWideChar( CP_ACP, 0, lpDP->dp2->lpSessionDesc->u1.lpszSessionNameA, -1,
                       (LPWSTR)(rmsg+1), dwVariableLen );
}