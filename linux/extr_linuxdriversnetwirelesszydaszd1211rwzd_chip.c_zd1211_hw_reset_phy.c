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
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  const member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
#define  ZD_CR0 268 
#define  ZD_CR1 267 
#define  ZD_CR10 266 
#define  ZD_CR100 265 
#define  ZD_CR101 264 
#define  ZD_CR102 263 
#define  ZD_CR103 262 
#define  ZD_CR104 261 
#define  ZD_CR105 260 
#define  ZD_CR106 259 
#define  ZD_CR107 258 
#define  ZD_CR108 257 
#define  ZD_CR109 256 
#define  ZD_CR11 255 
#define  ZD_CR110 254 
#define  ZD_CR111 253 
#define  ZD_CR112 252 
#define  ZD_CR113 251 
#define  ZD_CR114 250 
#define  ZD_CR115 249 
#define  ZD_CR116 248 
#define  ZD_CR117 247 
#define  ZD_CR118 246 
#define  ZD_CR119 245 
#define  ZD_CR12 244 
#define  ZD_CR120 243 
#define  ZD_CR125 242 
#define  ZD_CR126 241 
#define  ZD_CR127 240 
#define  ZD_CR128 239 
#define  ZD_CR129 238 
#define  ZD_CR13 237 
#define  ZD_CR130 236 
#define  ZD_CR131 235 
#define  ZD_CR136 234 
#define  ZD_CR137 233 
#define  ZD_CR138 232 
#define  ZD_CR139 231 
#define  ZD_CR14 230 
#define  ZD_CR140 229 
#define  ZD_CR141 228 
#define  ZD_CR142 227 
#define  ZD_CR143 226 
#define  ZD_CR144 225 
#define  ZD_CR147 224 
#define  ZD_CR148 223 
#define  ZD_CR149 222 
#define  ZD_CR15 221 
#define  ZD_CR150 220 
#define  ZD_CR151 219 
#define  ZD_CR16 218 
#define  ZD_CR160 217 
#define  ZD_CR161 216 
#define  ZD_CR162 215 
#define  ZD_CR163 214 
#define  ZD_CR164 213 
#define  ZD_CR165 212 
#define  ZD_CR166 211 
#define  ZD_CR167 210 
#define  ZD_CR168 209 
#define  ZD_CR169 208 
#define  ZD_CR17 207 
#define  ZD_CR170 206 
#define  ZD_CR171 205 
#define  ZD_CR18 204 
#define  ZD_CR19 203 
#define  ZD_CR2 202 
#define  ZD_CR20 201 
#define  ZD_CR203 200 
#define  ZD_CR204 199 
#define  ZD_CR21 198 
#define  ZD_CR22 197 
#define  ZD_CR23 196 
#define  ZD_CR24 195 
#define  ZD_CR25 194 
#define  ZD_CR26 193 
#define  ZD_CR27 192 
#define  ZD_CR28 191 
#define  ZD_CR29 190 
#define  ZD_CR3 189 
#define  ZD_CR30 188 
#define  ZD_CR31 187 
#define  ZD_CR32 186 
#define  ZD_CR33 185 
#define  ZD_CR34 184 
#define  ZD_CR35 183 
#define  ZD_CR36 182 
#define  ZD_CR37 181 
#define  ZD_CR38 180 
#define  ZD_CR39 179 
#define  ZD_CR4 178 
#define  ZD_CR40 177 
#define  ZD_CR41 176 
#define  ZD_CR42 175 
#define  ZD_CR43 174 
#define  ZD_CR44 173 
#define  ZD_CR46 172 
#define  ZD_CR47 171 
#define  ZD_CR48 170 
#define  ZD_CR49 169 
#define  ZD_CR5 168 
#define  ZD_CR6 167 
#define  ZD_CR64 166 
#define  ZD_CR65 165 
#define  ZD_CR66 164 
#define  ZD_CR67 163 
#define  ZD_CR68 162 
#define  ZD_CR69 161 
#define  ZD_CR7 160 
#define  ZD_CR70 159 
#define  ZD_CR71 158 
#define  ZD_CR72 157 
#define  ZD_CR73 156 
#define  ZD_CR74 155 
#define  ZD_CR75 154 
#define  ZD_CR76 153 
#define  ZD_CR77 152 
#define  ZD_CR78 151 
#define  ZD_CR79 150 
#define  ZD_CR8 149 
#define  ZD_CR80 148 
#define  ZD_CR81 147 
#define  ZD_CR82 146 
#define  ZD_CR83 145 
#define  ZD_CR84 144 
#define  ZD_CR85 143 
#define  ZD_CR86 142 
#define  ZD_CR87 141 
#define  ZD_CR88 140 
#define  ZD_CR89 139 
#define  ZD_CR9 138 
#define  ZD_CR90 137 
#define  ZD_CR91 136 
#define  ZD_CR92 135 
#define  ZD_CR93 134 
#define  ZD_CR94 133 
#define  ZD_CR95 132 
#define  ZD_CR96 131 
#define  ZD_CR97 130 
#define  ZD_CR98 129 
#define  ZD_CR99 128 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int patch_cr157 (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_chip_lock_phy_regs (struct zd_chip*) ; 
 int zd_chip_unlock_phy_regs (struct zd_chip*) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1211_hw_reset_phy(struct zd_chip *chip)
{
	static const struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR0,   0x0a }, { ZD_CR1,   0x06 }, { ZD_CR2,   0x26 },
		{ ZD_CR3,   0x38 }, { ZD_CR4,   0x80 }, { ZD_CR9,   0xa0 },
		{ ZD_CR10,  0x81 }, { ZD_CR11,  0x00 }, { ZD_CR12,  0x7f },
		{ ZD_CR13,  0x8c }, { ZD_CR14,  0x80 }, { ZD_CR15,  0x3d },
		{ ZD_CR16,  0x20 }, { ZD_CR17,  0x1e }, { ZD_CR18,  0x0a },
		{ ZD_CR19,  0x48 }, { ZD_CR20,  0x0c }, { ZD_CR21,  0x0c },
		{ ZD_CR22,  0x23 }, { ZD_CR23,  0x90 }, { ZD_CR24,  0x14 },
		{ ZD_CR25,  0x40 }, { ZD_CR26,  0x10 }, { ZD_CR27,  0x19 },
		{ ZD_CR28,  0x7f }, { ZD_CR29,  0x80 }, { ZD_CR30,  0x4b },
		{ ZD_CR31,  0x60 }, { ZD_CR32,  0x43 }, { ZD_CR33,  0x08 },
		{ ZD_CR34,  0x06 }, { ZD_CR35,  0x0a }, { ZD_CR36,  0x00 },
		{ ZD_CR37,  0x00 }, { ZD_CR38,  0x38 }, { ZD_CR39,  0x0c },
		{ ZD_CR40,  0x84 }, { ZD_CR41,  0x2a }, { ZD_CR42,  0x80 },
		{ ZD_CR43,  0x10 }, { ZD_CR44,  0x12 }, { ZD_CR46,  0xff },
		{ ZD_CR47,  0x1E }, { ZD_CR48,  0x26 }, { ZD_CR49,  0x5b },
		{ ZD_CR64,  0xd0 }, { ZD_CR65,  0x04 }, { ZD_CR66,  0x58 },
		{ ZD_CR67,  0xc9 }, { ZD_CR68,  0x88 }, { ZD_CR69,  0x41 },
		{ ZD_CR70,  0x23 }, { ZD_CR71,  0x10 }, { ZD_CR72,  0xff },
		{ ZD_CR73,  0x32 }, { ZD_CR74,  0x30 }, { ZD_CR75,  0x65 },
		{ ZD_CR76,  0x41 }, { ZD_CR77,  0x1b }, { ZD_CR78,  0x30 },
		{ ZD_CR79,  0x68 }, { ZD_CR80,  0x64 }, { ZD_CR81,  0x64 },
		{ ZD_CR82,  0x00 }, { ZD_CR83,  0x00 }, { ZD_CR84,  0x00 },
		{ ZD_CR85,  0x02 }, { ZD_CR86,  0x00 }, { ZD_CR87,  0x00 },
		{ ZD_CR88,  0xff }, { ZD_CR89,  0xfc }, { ZD_CR90,  0x00 },
		{ ZD_CR91,  0x00 }, { ZD_CR92,  0x00 }, { ZD_CR93,  0x08 },
		{ ZD_CR94,  0x00 }, { ZD_CR95,  0x00 }, { ZD_CR96,  0xff },
		{ ZD_CR97,  0xe7 }, { ZD_CR98,  0x00 }, { ZD_CR99,  0x00 },
		{ ZD_CR100, 0x00 }, { ZD_CR101, 0xae }, { ZD_CR102, 0x02 },
		{ ZD_CR103, 0x00 }, { ZD_CR104, 0x03 }, { ZD_CR105, 0x65 },
		{ ZD_CR106, 0x04 }, { ZD_CR107, 0x00 }, { ZD_CR108, 0x0a },
		{ ZD_CR109, 0xaa }, { ZD_CR110, 0xaa }, { ZD_CR111, 0x25 },
		{ ZD_CR112, 0x25 }, { ZD_CR113, 0x00 }, { ZD_CR119, 0x1e },
		{ ZD_CR125, 0x90 }, { ZD_CR126, 0x00 }, { ZD_CR127, 0x00 },
		{ },
		{ ZD_CR5,   0x00 }, { ZD_CR6,   0x00 }, { ZD_CR7,   0x00 },
		{ ZD_CR8,   0x00 }, { ZD_CR9,   0x20 }, { ZD_CR12,  0xf0 },
		{ ZD_CR20,  0x0e }, { ZD_CR21,  0x0e }, { ZD_CR27,  0x10 },
		{ ZD_CR44,  0x33 }, { ZD_CR47,  0x1E }, { ZD_CR83,  0x24 },
		{ ZD_CR84,  0x04 }, { ZD_CR85,  0x00 }, { ZD_CR86,  0x0C },
		{ ZD_CR87,  0x12 }, { ZD_CR88,  0x0C }, { ZD_CR89,  0x00 },
		{ ZD_CR90,  0x10 }, { ZD_CR91,  0x08 }, { ZD_CR93,  0x00 },
		{ ZD_CR94,  0x01 }, { ZD_CR95,  0x00 }, { ZD_CR96,  0x50 },
		{ ZD_CR97,  0x37 }, { ZD_CR98,  0x35 }, { ZD_CR101, 0x13 },
		{ ZD_CR102, 0x27 }, { ZD_CR103, 0x27 }, { ZD_CR104, 0x18 },
		{ ZD_CR105, 0x12 }, { ZD_CR109, 0x27 }, { ZD_CR110, 0x27 },
		{ ZD_CR111, 0x27 }, { ZD_CR112, 0x27 }, { ZD_CR113, 0x27 },
		{ ZD_CR114, 0x27 }, { ZD_CR115, 0x26 }, { ZD_CR116, 0x24 },
		{ ZD_CR117, 0xfc }, { ZD_CR118, 0xfa }, { ZD_CR120, 0x4f },
		{ ZD_CR125, 0xaa }, { ZD_CR127, 0x03 }, { ZD_CR128, 0x14 },
		{ ZD_CR129, 0x12 }, { ZD_CR130, 0x10 }, { ZD_CR131, 0x0C },
		{ ZD_CR136, 0xdf }, { ZD_CR137, 0x40 }, { ZD_CR138, 0xa0 },
		{ ZD_CR139, 0xb0 }, { ZD_CR140, 0x99 }, { ZD_CR141, 0x82 },
		{ ZD_CR142, 0x54 }, { ZD_CR143, 0x1c }, { ZD_CR144, 0x6c },
		{ ZD_CR147, 0x07 }, { ZD_CR148, 0x4c }, { ZD_CR149, 0x50 },
		{ ZD_CR150, 0x0e }, { ZD_CR151, 0x18 }, { ZD_CR160, 0xfe },
		{ ZD_CR161, 0xee }, { ZD_CR162, 0xaa }, { ZD_CR163, 0xfa },
		{ ZD_CR164, 0xfa }, { ZD_CR165, 0xea }, { ZD_CR166, 0xbe },
		{ ZD_CR167, 0xbe }, { ZD_CR168, 0x6a }, { ZD_CR169, 0xba },
		{ ZD_CR170, 0xba }, { ZD_CR171, 0xba },
		/* Note: ZD_CR204 must lead the ZD_CR203 */
		{ ZD_CR204, 0x7d },
		{ },
		{ ZD_CR203, 0x30 },
	};

	int r, t;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	r = zd_chip_lock_phy_regs(chip);
	if (r)
		goto out;

	r = zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	if (r)
		goto unlock;

	r = patch_cr157(chip);
unlock:
	t = zd_chip_unlock_phy_regs(chip);
	if (t && !r)
		r = t;
out:
	return r;
}