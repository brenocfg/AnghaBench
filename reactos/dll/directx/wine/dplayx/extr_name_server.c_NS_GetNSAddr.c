#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* lpNSCache ;
struct TYPE_5__ {TYPE_1__* lpQHFirst; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpRemoteAddrHdr; int /*<<< orphan*/ * lpLocalAddrHdr; scalar_t__ bNsIsLocal; TYPE_2__ first; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpNSAddrHdr; } ;
typedef  int /*<<< orphan*/ * LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 

LPVOID NS_GetNSAddr( LPVOID lpNSInfo )
{
  lpNSCache lpCache = (lpNSCache)lpNSInfo;

  FIXME( ":quick stub\n" );

  /* Ok. Cheat and don't search for the correct stuff just take the first.
   * FIXME: In the future how are we to know what is _THE_ enum we used?
   *        This is going to have to go into dplay somehow. Perhaps it
   *        comes back with app server id for the join command! Oh... that
   *        must be it. That would make this method obsolete once that's
   *        in place.
   */
#if 1
  if ( lpCache->first.lpQHFirst )
    return lpCache->first.lpQHFirst->lpNSAddrHdr;

  return NULL;
#else
  /* FIXME: Should convert over to this */
  return lpCache->bNsIsLocal ? lpCache->lpLocalAddrHdr
                             : lpCache->lpRemoteAddrHdr;
#endif
}