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

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ B43_NTAB_BDI_SIZE ; 
 scalar_t__ B43_NTAB_C0_ADJPLT_SIZE ; 
 scalar_t__ B43_NTAB_C0_ESTPLT_SIZE ; 
 scalar_t__ B43_NTAB_C0_GAINCTL_SIZE ; 
 scalar_t__ B43_NTAB_C0_IQLT_SIZE ; 
 scalar_t__ B43_NTAB_C0_LOFEEDTH_SIZE ; 
 scalar_t__ B43_NTAB_C1_ADJPLT_SIZE ; 
 scalar_t__ B43_NTAB_C1_ESTPLT_SIZE ; 
 scalar_t__ B43_NTAB_C1_GAINCTL_SIZE ; 
 scalar_t__ B43_NTAB_C1_IQLT_SIZE ; 
 scalar_t__ B43_NTAB_C1_LOFEEDTH_SIZE ; 
 scalar_t__ B43_NTAB_CHANEST_SIZE ; 
 scalar_t__ B43_NTAB_FRAMELT_SIZE ; 
 scalar_t__ B43_NTAB_FRAMESTRUCT_SIZE ; 
 scalar_t__ B43_NTAB_INTLEVEL_SIZE ; 
 scalar_t__ B43_NTAB_MCS_SIZE ; 
 scalar_t__ B43_NTAB_NOISEVAR10_SIZE ; 
 scalar_t__ B43_NTAB_NOISEVAR11_SIZE ; 
 scalar_t__ B43_NTAB_PILOTLT_SIZE ; 
 scalar_t__ B43_NTAB_PILOT_SIZE ; 
 scalar_t__ B43_NTAB_TDI20A0_SIZE ; 
 scalar_t__ B43_NTAB_TDI20A1_SIZE ; 
 scalar_t__ B43_NTAB_TDI40A0_SIZE ; 
 scalar_t__ B43_NTAB_TDI40A1_SIZE ; 
 scalar_t__ B43_NTAB_TDTRN_SIZE ; 
 scalar_t__ B43_NTAB_TMAP_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  b43_ntab_adjustpower0 ; 
 int /*<<< orphan*/  b43_ntab_adjustpower1 ; 
 int /*<<< orphan*/  b43_ntab_bdi ; 
 int /*<<< orphan*/  b43_ntab_channelest ; 
 int /*<<< orphan*/  b43_ntab_estimatepowerlt0 ; 
 int /*<<< orphan*/  b43_ntab_estimatepowerlt1 ; 
 int /*<<< orphan*/  b43_ntab_framelookup ; 
 int /*<<< orphan*/  b43_ntab_framestruct ; 
 int /*<<< orphan*/  b43_ntab_gainctl0 ; 
 int /*<<< orphan*/  b43_ntab_gainctl1 ; 
 int /*<<< orphan*/  b43_ntab_intlevel ; 
 int /*<<< orphan*/  b43_ntab_iqlt0 ; 
 int /*<<< orphan*/  b43_ntab_iqlt1 ; 
 int /*<<< orphan*/  b43_ntab_loftlt0 ; 
 int /*<<< orphan*/  b43_ntab_loftlt1 ; 
 int /*<<< orphan*/  b43_ntab_mcs ; 
 int /*<<< orphan*/  b43_ntab_noisevar10 ; 
 int /*<<< orphan*/  b43_ntab_noisevar11 ; 
 int /*<<< orphan*/  b43_ntab_pilot ; 
 int /*<<< orphan*/  b43_ntab_pilotlt ; 
 int /*<<< orphan*/  b43_ntab_tdi20a0 ; 
 int /*<<< orphan*/  b43_ntab_tdi20a1 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a0 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a1 ; 
 int /*<<< orphan*/  b43_ntab_tdtrn ; 
 int /*<<< orphan*/  b43_ntab_tmap ; 

__attribute__((used)) static inline void assert_ntab_array_sizes(void)
{
#undef check
#define check(table, size)	\
	BUILD_BUG_ON(ARRAY_SIZE(b43_ntab_##table) != B43_NTAB_##size##_SIZE)

	check(adjustpower0, C0_ADJPLT);
	check(adjustpower1, C1_ADJPLT);
	check(bdi, BDI);
	check(channelest, CHANEST);
	check(estimatepowerlt0, C0_ESTPLT);
	check(estimatepowerlt1, C1_ESTPLT);
	check(framelookup, FRAMELT);
	check(framestruct, FRAMESTRUCT);
	check(gainctl0, C0_GAINCTL);
	check(gainctl1, C1_GAINCTL);
	check(intlevel, INTLEVEL);
	check(iqlt0, C0_IQLT);
	check(iqlt1, C1_IQLT);
	check(loftlt0, C0_LOFEEDTH);
	check(loftlt1, C1_LOFEEDTH);
	check(mcs, MCS);
	check(noisevar10, NOISEVAR10);
	check(noisevar11, NOISEVAR11);
	check(pilot, PILOT);
	check(pilotlt, PILOTLT);
	check(tdi20a0, TDI20A0);
	check(tdi20a1, TDI20A1);
	check(tdi40a0, TDI40A0);
	check(tdi40a1, TDI40A1);
	check(tdtrn, TDTRN);
	check(tmap, TMAP);

#undef check
}