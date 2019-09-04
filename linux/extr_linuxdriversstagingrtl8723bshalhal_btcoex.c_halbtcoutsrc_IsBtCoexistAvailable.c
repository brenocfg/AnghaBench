#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * Adapter; int /*<<< orphan*/  bBinded; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */

__attribute__((used)) static u8 halbtcoutsrc_IsBtCoexistAvailable(PBTC_COEXIST pBtCoexist)
{
	if (!pBtCoexist->bBinded ||
		NULL == pBtCoexist->Adapter){
		return false;
	}
	return true;
}