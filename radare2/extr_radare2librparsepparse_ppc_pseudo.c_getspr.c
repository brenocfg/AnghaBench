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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  cspr ;

/* Variables and functions */
#define  SPR_CTR 202 
#define  SPR_DABR 201 
#define  SPR_DAR 200 
#define  SPR_DBAT0L 199 
#define  SPR_DBAT0U 198 
#define  SPR_DBAT1L 197 
#define  SPR_DBAT1U 196 
#define  SPR_DBAT2L 195 
#define  SPR_DBAT2U 194 
#define  SPR_DBAT3L 193 
#define  SPR_DBAT3U 192 
#define  SPR_DCMP 191 
#define  SPR_DEC 190 
#define  SPR_DMISS 189 
#define  SPR_DSISR 188 
#define  SPR_EAR 187 
#define  SPR_HASH1 186 
#define  SPR_HASH2 185 
#define  SPR_HID0 184 
#define  SPR_HID1 183 
#define  SPR_HID2 182 
#define  SPR_HID4 181 
#define  SPR_HID5 180 
#define  SPR_HID6 179 
#define  SPR_IABR 178 
#define  SPR_IBAT0L 177 
#define  SPR_IBAT0U 176 
#define  SPR_IBAT1L 175 
#define  SPR_IBAT1U 174 
#define  SPR_IBAT2L 173 
#define  SPR_IBAT2U 172 
#define  SPR_IBAT3L 171 
#define  SPR_IBAT3U 170 
#define  SPR_ICMP 169 
#define  SPR_ICTC 168 
#define  SPR_IMISS 167 
#define  SPR_LR 166 
#define  SPR_MMCR0 165 
#define  SPR_MMCR1 164 
#define  SPR_MQ 163 
#define  SPR_PIR 162 
#define  SPR_PMC1 161 
#define  SPR_PMC2 160 
#define  SPR_PMC3 159 
#define  SPR_PMC4 158 
#define  SPR_PVR 157 
#define  SPR_RPA 156 
#define  SPR_RTCL 155 
#define  SPR_RTCU 154 
#define  SPR_SDA 153 
#define  SPR_SDR1 152 
#define  SPR_SIA 151 
#define  SPR_SPEFSCR 150 
#define  SPR_SPRG0 149 
#define  SPR_SPRG1 148 
#define  SPR_SPRG2 147 
#define  SPR_SPRG3 146 
#define  SPR_SRR0 145 
#define  SPR_SRR1 144 
#define  SPR_TBL 143 
#define  SPR_TBRL 142 
#define  SPR_TBRU 141 
#define  SPR_TBU 140 
#define  SPR_THRM1 139 
#define  SPR_THRM2 138 
#define  SPR_THRM3 137 
#define  SPR_UMMCR0 136 
#define  SPR_UMMCR1 135 
#define  SPR_UPMC1 134 
#define  SPR_UPMC2 133 
#define  SPR_UPMC3 132 
#define  SPR_UPMC4 131 
#define  SPR_USIA 130 
#define  SPR_VRSAVE 129 
#define  SPR_XER 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char* getspr(const char *reg) {
	static char cspr[16];
	ut32 spr = 0;
	if (!reg) {
		return NULL;
	}
	spr = strtol(reg, NULL, 16);
	if (spr > 9999) {
		return NULL; //just to avoid overflows..
	}

	switch (spr) {
		case SPR_MQ:
			return "mq";
		case SPR_XER:
			return "xer";
		case SPR_RTCU:
			return "rtcu";
		case SPR_RTCL:
			return "rtcl";
		case SPR_LR:
			return "lr";
		case SPR_CTR:
			return "ctr";
		case SPR_DSISR:
			return "dsisr";
		case SPR_DAR:
			return "dar";
		case SPR_DEC:
			return "dec";
		case SPR_SDR1:
			return "sdr1";
		case SPR_SRR0:
			return "srr0";
		case SPR_SRR1:
			return "srr1";
		case SPR_VRSAVE:
			return "vrsave";
		case SPR_TBRL:
			return "tbrl";
		case SPR_TBRU:
			return "tbru";
		case SPR_SPRG0:
			return "sprg0";
		case SPR_SPRG1:
			return "sprg1";
		case SPR_SPRG2:
			return "sprg2";
		case SPR_SPRG3:
			return "sprg3";
		case SPR_EAR:
			return "ear";
		case SPR_TBL:
			return "tbl";
		case SPR_TBU:
			return "tbu";
		case SPR_PVR:
			return "pvr";
		case SPR_SPEFSCR:
			return "spefscr";
		case SPR_IBAT0U:
			return "ibat0u";
		case SPR_IBAT0L:
			return "ibat0l";
		case SPR_IBAT1U:
			return "ibat1u";
		case SPR_IBAT1L:
			return "ibat1l";
		case SPR_IBAT2U:
			return "ibat2u";
		case SPR_IBAT2L:
			return "ibat2l";
		case SPR_IBAT3U:
			return "ibat3u";
		case SPR_IBAT3L:
			return "ibat3l";
		case SPR_DBAT0U:
			return "dbat0u";
		case SPR_DBAT0L:
			return "dbat0l";
		case SPR_DBAT1U:
			return "dbat1u";
		case SPR_DBAT1L:
			return "dbat1l";
		case SPR_DBAT2U:
			return "dbat2u";
		case SPR_DBAT2L:
			return "dbat2l";
		case SPR_DBAT3U:
			return "dbat3u";
		case SPR_DBAT3L:
			return "dbat3l";
		case SPR_UMMCR0:
			return "ummcr0";
		case SPR_UMMCR1:
			return "ummcr1";
		case SPR_UPMC1:
			return "upmc1";
		case SPR_UPMC2:
			return "upmc2";
		case SPR_USIA:
			return "usia";
		case SPR_UPMC3:
			return "upmc3";
		case SPR_UPMC4:
			return "upmc4";
		case SPR_MMCR0:
			return "mmcr0";
		case SPR_PMC1:
			return "pmc1";
		case SPR_PMC2:
			return "pmc2";
		case SPR_SIA:
			return "sia";
		case SPR_MMCR1:
			return "mmcr1";
		case SPR_PMC3:
			return "pmc3";
		case SPR_PMC4:
			return "pmc4";
		case SPR_SDA:
			return "sda";
		case SPR_DMISS:
			return "dmiss";
		case SPR_DCMP:
			return "dcmp";
		case SPR_HASH1:
			return "hash1";
		case SPR_HASH2:
			return "hash2";
		case SPR_IMISS:
			return "imiss";
		case SPR_ICMP:
			return "icmp";
		case SPR_RPA:
			return "rpa";
		case SPR_HID0:
			return "hid0";
		case SPR_HID1:
			return "hid1";
		case SPR_IABR:
			return "iabr";
		case SPR_HID2:
			return "hid2";
		case SPR_HID4:
			return "hid4";
		case SPR_DABR:
			return "dabr";
		case SPR_HID5:
			return "hid5";
		case SPR_HID6:
			return "hid6";
//		case SPR_L2CR:
//			return "l2cr";
		case SPR_ICTC:
			return "ictc";
		case SPR_THRM1:
			return "thrm1";
		case SPR_THRM2:
			return "thrm2";
		case SPR_THRM3:
			return "thrm3";
		case SPR_PIR:
			return "pir";
		default:
			snprintf(cspr, sizeof(cspr), "spr_%u", spr);
			break;
	}
	return cspr;
}