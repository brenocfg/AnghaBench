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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_sprom {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSB_SPROM2_BFLHI ; 
 int /*<<< orphan*/  SSB_SPROM2_MAXP_A ; 
 int SSB_SPROM2_MAXP_A_HI ; 
 int SSB_SPROM2_MAXP_A_LO ; 
 int /*<<< orphan*/  SSB_SPROM2_MAXP_A_LO_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM2_OPO ; 
 int SSB_SPROM2_OPO_VALUE ; 
 int /*<<< orphan*/  SSB_SPROM2_PA1HIB0 ; 
 int /*<<< orphan*/  SSB_SPROM2_PA1HIB1 ; 
 int /*<<< orphan*/  SSB_SPROM2_PA1HIB2 ; 
 int /*<<< orphan*/  SSB_SPROM2_PA1LOB0 ; 
 int /*<<< orphan*/  SSB_SPROM2_PA1LOB1 ; 
 int /*<<< orphan*/  SSB_SPROM2_PA1LOB2 ; 
 int /*<<< orphan*/  boardflags_hi ; 
 int /*<<< orphan*/  maxpwr_ah ; 
 int /*<<< orphan*/  maxpwr_al ; 
 int /*<<< orphan*/  opo ; 
 int /*<<< orphan*/  pa1hib0 ; 
 int /*<<< orphan*/  pa1hib1 ; 
 int /*<<< orphan*/  pa1hib2 ; 
 int /*<<< orphan*/  pa1lob0 ; 
 int /*<<< orphan*/  pa1lob1 ; 
 int /*<<< orphan*/  pa1lob2 ; 

__attribute__((used)) static void sprom_extract_r23(struct ssb_sprom *out, const u16 *in)
{
	SPEX(boardflags_hi, SSB_SPROM2_BFLHI, 0xFFFF, 0);
	SPEX(opo, SSB_SPROM2_OPO, SSB_SPROM2_OPO_VALUE, 0);
	SPEX(pa1lob0, SSB_SPROM2_PA1LOB0, 0xFFFF, 0);
	SPEX(pa1lob1, SSB_SPROM2_PA1LOB1, 0xFFFF, 0);
	SPEX(pa1lob2, SSB_SPROM2_PA1LOB2, 0xFFFF, 0);
	SPEX(pa1hib0, SSB_SPROM2_PA1HIB0, 0xFFFF, 0);
	SPEX(pa1hib1, SSB_SPROM2_PA1HIB1, 0xFFFF, 0);
	SPEX(pa1hib2, SSB_SPROM2_PA1HIB2, 0xFFFF, 0);
	SPEX(maxpwr_ah, SSB_SPROM2_MAXP_A, SSB_SPROM2_MAXP_A_HI, 0);
	SPEX(maxpwr_al, SSB_SPROM2_MAXP_A, SSB_SPROM2_MAXP_A_LO,
	     SSB_SPROM2_MAXP_A_LO_SHIFT);
}