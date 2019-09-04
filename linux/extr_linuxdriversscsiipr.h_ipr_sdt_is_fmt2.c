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
typedef  int u32 ;

/* Variables and functions */
 int IPR_GET_FMT2_BAR_SEL (int) ; 
#define  IPR_SDT_FMT2_BAR0_SEL 134 
#define  IPR_SDT_FMT2_BAR1_SEL 133 
#define  IPR_SDT_FMT2_BAR2_SEL 132 
#define  IPR_SDT_FMT2_BAR3_SEL 131 
#define  IPR_SDT_FMT2_BAR4_SEL 130 
#define  IPR_SDT_FMT2_BAR5_SEL 129 
#define  IPR_SDT_FMT2_EXP_ROM_SEL 128 

__attribute__((used)) static inline int ipr_sdt_is_fmt2(u32 sdt_word)
{
	u32 bar_sel = IPR_GET_FMT2_BAR_SEL(sdt_word);

	switch (bar_sel) {
	case IPR_SDT_FMT2_BAR0_SEL:
	case IPR_SDT_FMT2_BAR1_SEL:
	case IPR_SDT_FMT2_BAR2_SEL:
	case IPR_SDT_FMT2_BAR3_SEL:
	case IPR_SDT_FMT2_BAR4_SEL:
	case IPR_SDT_FMT2_BAR5_SEL:
	case IPR_SDT_FMT2_EXP_ROM_SEL:
		return 1;
	};

	return 0;
}