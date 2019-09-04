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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  btRealFwVer; } ;
struct TYPE_5__ {TYPE_1__ btInfo; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */

__attribute__((used)) static u32 halbtcoutsrc_GetBtPatchVer(PBTC_COEXIST pBtCoexist)
{
	return pBtCoexist->btInfo.btRealFwVer;
}