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
typedef  TYPE_1__* lpNSCache ;
struct TYPE_2__ {int /*<<< orphan*/  bNsIsLocal; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCDPSESSIONDESC2 ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

void NS_SetLocalComputerAsNameServer( LPCDPSESSIONDESC2 lpsd, LPVOID lpNSInfo )
{
  lpNSCache lpCache = (lpNSCache)lpNSInfo;

  lpCache->bNsIsLocal = TRUE;
}