#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* lpPlayerList ;
struct TYPE_5__ {TYPE_1__* lpPData; } ;
struct TYPE_4__ {void* lpSPPlayerData; } ;
typedef  int /*<<< orphan*/  IDirectPlayImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DPID ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_INVALIDPLAYER ; 
 TYPE_2__* DP_FindPlayer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_OK ; 

HRESULT DP_SetSPPlayerData( IDirectPlayImpl *lpDP, DPID idPlayer, void *lpData )
{
  lpPlayerList lpPlayer = DP_FindPlayer( lpDP, idPlayer );

  if( lpPlayer == NULL )
  {
    return DPERR_INVALIDPLAYER;
  }

  lpPlayer->lpPData->lpSPPlayerData = lpData;

  return DP_OK;
}