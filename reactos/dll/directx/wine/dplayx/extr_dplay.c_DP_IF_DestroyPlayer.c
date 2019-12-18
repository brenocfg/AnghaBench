#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  bAnsi; void* idPlayer; TYPE_4__* This; } ;
struct TYPE_16__ {int /*<<< orphan*/  lpISP; scalar_t__ dwFlags; void* idPlayer; } ;
struct TYPE_15__ {TYPE_3__* dp2; int /*<<< orphan*/  IDirectPlay4_iface; } ;
struct TYPE_13__ {TYPE_1__* lpCB; int /*<<< orphan*/  lpISP; } ;
struct TYPE_14__ {scalar_t__ connectionInitialized; TYPE_2__ spData; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* DeletePlayer ) (TYPE_5__*) ;} ;
typedef  TYPE_4__ IDirectPlayImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_5__ DPSP_DELETEPLAYERDATA ;
typedef  void* DPID ;
typedef  TYPE_6__ DPFAGContext ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPENUMGROUPS_ALL ; 
 int /*<<< orphan*/  DPERR_INVALIDPLAYER ; 
 int /*<<< orphan*/  DPERR_UNINITIALIZED ; 
 int /*<<< orphan*/  DP_DeletePlayer (TYPE_4__*,void*) ; 
 int /*<<< orphan*/ * DP_FindPlayer (TYPE_4__*,void*) ; 
 int /*<<< orphan*/  DP_OK ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IDirectPlayX_EnumGroups (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ NO_PROVIDER ; 
 int /*<<< orphan*/  cbDeletePlayerFromAllGroups ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static HRESULT DP_IF_DestroyPlayer( IDirectPlayImpl *This, void *lpMsgHdr, DPID idPlayer,
        BOOL bAnsi )
{
  DPFAGContext cbContext;

  FIXME( "(%p)->(%p,0x%08x,%u): semi stub\n",
         This, lpMsgHdr, idPlayer, bAnsi );

  if( This->dp2->connectionInitialized == NO_PROVIDER )
  {
    return DPERR_UNINITIALIZED;
  }

  if( DP_FindPlayer( This, idPlayer ) == NULL )
  {
    return DPERR_INVALIDPLAYER;
  }

  /* FIXME: If the player is remote, we must be the host to delete this */

  cbContext.This     = This;
  cbContext.idPlayer = idPlayer;
  cbContext.bAnsi    = bAnsi;

  /* Find each group and call DeletePlayerFromGroup if the player is a
     member of the group */
  IDirectPlayX_EnumGroups( &This->IDirectPlay4_iface, NULL, cbDeletePlayerFromAllGroups, &cbContext,
          DPENUMGROUPS_ALL );

  /* Now delete player and player list from the sys group */
  DP_DeletePlayer( This, idPlayer );

  /* Let the SP know that we've destroyed this group */
  if( This->dp2->spData.lpCB->DeletePlayer )
  {
    DPSP_DELETEPLAYERDATA data;

    FIXME( "data.dwFlags is incorrect\n" );

    data.idPlayer = idPlayer;
    data.dwFlags = 0;
    data.lpISP   = This->dp2->spData.lpISP;

    (*This->dp2->spData.lpCB->DeletePlayer)( &data );
  }

  FIXME( "Send a DELETEPLAYERORGROUP msg\n" );

  return DP_OK;
}