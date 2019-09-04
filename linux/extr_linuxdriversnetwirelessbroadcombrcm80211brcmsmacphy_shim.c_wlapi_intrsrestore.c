#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct phy_shim_info {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_intrsrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wlapi_intrsrestore(struct phy_shim_info *physhim, u32 macintmask)
{
	brcms_intrsrestore(physhim->wl, macintmask);
}