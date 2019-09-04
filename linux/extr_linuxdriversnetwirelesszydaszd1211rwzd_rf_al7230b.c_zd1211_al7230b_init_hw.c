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
struct zd_rf {int dummy; } ;
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  const member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
#define  ZD_CR10 178 
#define  ZD_CR100 177 
#define  ZD_CR101 176 
#define  ZD_CR102 175 
#define  ZD_CR106 174 
#define  ZD_CR107 173 
#define  ZD_CR109 172 
#define  ZD_CR110 171 
#define  ZD_CR111 170 
#define  ZD_CR112 169 
#define  ZD_CR113 168 
#define  ZD_CR114 167 
#define  ZD_CR115 166 
#define  ZD_CR116 165 
#define  ZD_CR117 164 
#define  ZD_CR118 163 
#define  ZD_CR119 162 
#define  ZD_CR120 161 
#define  ZD_CR121 160 
#define  ZD_CR122 159 
#define  ZD_CR128 158 
#define  ZD_CR129 157 
#define  ZD_CR130 156 
#define  ZD_CR136 155 
#define  ZD_CR137 154 
#define  ZD_CR138 153 
#define  ZD_CR15 152 
#define  ZD_CR17 151 
 int /*<<< orphan*/  const ZD_CR203 ; 
#define  ZD_CR23 150 
#define  ZD_CR24 149 
#define  ZD_CR240 148 
#define  ZD_CR251 147 
#define  ZD_CR252 146 
#define  ZD_CR253 145 
#define  ZD_CR26 144 
#define  ZD_CR28 143 
#define  ZD_CR29 142 
#define  ZD_CR34 141 
#define  ZD_CR35 140 
#define  ZD_CR38 139 
#define  ZD_CR41 138 
#define  ZD_CR44 137 
#define  ZD_CR46 136 
#define  ZD_CR47 135 
#define  ZD_CR79 134 
#define  ZD_CR80 133 
#define  ZD_CR81 132 
#define  ZD_CR87 131 
#define  ZD_CR89 130 
#define  ZD_CR92 129 
#define  ZD_CR99 128 
 struct zd_ioreq16 const** chan_rv ; 
 struct zd_ioreq16 const* rv_init1 ; 
 struct zd_ioreq16 const* rv_init2 ; 
 struct zd_ioreq16 const* std_rv ; 
 int zd_iowrite16_locked (struct zd_chip*,int,int /*<<< orphan*/  const) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 
 int zd_rfwritev_cr_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1211_al7230b_init_hw(struct zd_rf *rf)
{
	int r;
	struct zd_chip *chip = zd_rf_to_chip(rf);

	/* All of these writes are identical to AL2230 unless otherwise
	 * specified */
	static const struct zd_ioreq16 ioreqs_1[] = {
		/* This one is 7230-specific, and happens before the rest */
		{ ZD_CR240,  0x57 },
		{ },

		{ ZD_CR15,   0x20 }, { ZD_CR23,   0x40 }, { ZD_CR24,  0x20 },
		{ ZD_CR26,   0x11 }, { ZD_CR28,   0x3e }, { ZD_CR29,  0x00 },
		{ ZD_CR44,   0x33 },
		/* This value is different for 7230 (was: 0x2a) */
		{ ZD_CR106,  0x22 },
		{ ZD_CR107,  0x1a }, { ZD_CR109,  0x09 }, { ZD_CR110,  0x27 },
		{ ZD_CR111,  0x2b }, { ZD_CR112,  0x2b }, { ZD_CR119,  0x0a },
		/* This happened further down in AL2230,
		 * and the value changed (was: 0xe0) */
		{ ZD_CR122,  0xfc },
		{ ZD_CR10,   0x89 },
		/* for newest (3rd cut) AL2300 */
		{ ZD_CR17,   0x28 },
		{ ZD_CR26,   0x93 }, { ZD_CR34,   0x30 },
		/* for newest (3rd cut) AL2300 */
		{ ZD_CR35,   0x3e },
		{ ZD_CR41,   0x24 }, { ZD_CR44,   0x32 },
		/* for newest (3rd cut) AL2300 */
		{ ZD_CR46,   0x96 },
		{ ZD_CR47,   0x1e }, { ZD_CR79,   0x58 }, { ZD_CR80,  0x30 },
		{ ZD_CR81,   0x30 }, { ZD_CR87,   0x0a }, { ZD_CR89,  0x04 },
		{ ZD_CR92,   0x0a }, { ZD_CR99,   0x28 },
		/* This value is different for 7230 (was: 0x00) */
		{ ZD_CR100,  0x02 },
		{ ZD_CR101,  0x13 }, { ZD_CR102,  0x27 },
		/* This value is different for 7230 (was: 0x24) */
		{ ZD_CR106,  0x22 },
		/* This value is different for 7230 (was: 0x2a) */
		{ ZD_CR107,  0x3f },
		{ ZD_CR109,  0x09 },
		/* This value is different for 7230 (was: 0x13) */
		{ ZD_CR110,  0x1f },
		{ ZD_CR111,  0x1f }, { ZD_CR112,  0x1f }, { ZD_CR113, 0x27 },
		{ ZD_CR114,  0x27 },
		/* for newest (3rd cut) AL2300 */
		{ ZD_CR115,  0x24 },
		/* This value is different for 7230 (was: 0x24) */
		{ ZD_CR116,  0x3f },
		/* This value is different for 7230 (was: 0xf4) */
		{ ZD_CR117,  0xfa },
		{ ZD_CR118,  0xfc }, { ZD_CR119,  0x10 }, { ZD_CR120, 0x4f },
		{ ZD_CR121,  0x77 }, { ZD_CR137,  0x88 },
		/* This one is 7230-specific */
		{ ZD_CR138,  0xa8 },
		/* This value is different for 7230 (was: 0xff) */
		{ ZD_CR252,  0x34 },
		/* This value is different for 7230 (was: 0xff) */
		{ ZD_CR253,  0x34 },

		/* PLL_OFF */
		{ ZD_CR251, 0x2f },
	};

	static const struct zd_ioreq16 ioreqs_2[] = {
		{ ZD_CR251, 0x3f }, /* PLL_ON */
		{ ZD_CR128, 0x14 }, { ZD_CR129, 0x12 }, { ZD_CR130, 0x10 },
		{ ZD_CR38,  0x38 }, { ZD_CR136, 0xdf },
	};

	r = zd_iowrite16a_locked(chip, ioreqs_1, ARRAY_SIZE(ioreqs_1));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, chan_rv[0], ARRAY_SIZE(chan_rv[0]));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, std_rv, ARRAY_SIZE(std_rv));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, rv_init1, ARRAY_SIZE(rv_init1));
	if (r)
		return r;

	r = zd_iowrite16a_locked(chip, ioreqs_2, ARRAY_SIZE(ioreqs_2));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, rv_init2, ARRAY_SIZE(rv_init2));
	if (r)
		return r;

	r = zd_iowrite16_locked(chip, 0x06, ZD_CR203);
	if (r)
		return r;
	r = zd_iowrite16_locked(chip, 0x80, ZD_CR240);
	if (r)
		return r;

	return 0;
}