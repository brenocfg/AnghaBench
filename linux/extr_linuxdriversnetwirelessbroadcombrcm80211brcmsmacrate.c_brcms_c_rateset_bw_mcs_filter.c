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
typedef  scalar_t__ u8 ;
struct brcms_c_rateset {int /*<<< orphan*/  mcs; } ;

/* Variables and functions */
 scalar_t__ BRCMS_40_MHZ ; 
 int /*<<< orphan*/  clrbit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,int) ; 

void brcms_c_rateset_bw_mcs_filter(struct brcms_c_rateset *rateset, u8 bw)
{
	if (bw == BRCMS_40_MHZ)
		setbit(rateset->mcs, 32);
	else
		clrbit(rateset->mcs, 32);
}