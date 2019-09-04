#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
typedef  int ret ;
typedef  int n ;
typedef  int dst ;
struct TYPE_6__ {char* name; int code; int type; } ;
struct TYPE_5__ {char* op; int o; char** a; scalar_t__ off; } ;
typedef  TYPE_1__ ArmOpcode ;

/* Variables and functions */
#define  TYPE_ARI 147 
#define  TYPE_BKP 146 
#define  TYPE_BRA 145 
#define  TYPE_BRR 144 
#define  TYPE_CLZ 143 
#define  TYPE_COPROC 142 
#define  TYPE_ENDIAN 141 
#define  TYPE_HLT 140 
#define  TYPE_IMM 139 
#define  TYPE_MEM 138 
#define  TYPE_MOV 137 
#define  TYPE_MOVT 136 
#define  TYPE_MOVW 135 
#define  TYPE_MUL 134 
#define  TYPE_REV 133 
#define  TYPE_SHFT 132 
#define  TYPE_SWI 131 
#define  TYPE_SWP 130 
#define  TYPE_TST 129 
#define  TYPE_UDF 128 
 int /*<<< orphan*/  arm_opcode_cond (TYPE_1__*,int) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  findyz (int,int*,int*) ; 
 int getimmed8 (char*) ; 
 int getnum (char const*) ; 
 int /*<<< orphan*/  getrange (char*) ; 
 int getreg (char*) ; 
 int getshift (char*) ; 
 TYPE_2__* ops ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcmpnull (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static int arm_assemble(ArmOpcode *ao, ut64 off, const char *str) {
	int i, j, ret, reg, a, b;
	int coproc, opc;
	bool rex = false;
	int shift, low, high;
	for (i = 0; ops[i].name; i++) {
		if (!strncmp (ao->op, ops[i].name, strlen (ops[i].name))) {
			ao->o = ops[i].code;
			arm_opcode_cond (ao, strlen(ops[i].name));
			if (ao->a[0] || ops[i].type == TYPE_BKP) {
				switch (ops[i].type) {
				case TYPE_MEM:
					if (!strncmp (ops[i].name, "strex", 5)) {
						rex = 1;
					}
					if (!strcmp (ops[i].name, "str") || !strcmp (ops[i].name, "ldr")) {
						if (!ao->a[2]) {
							ao->a[2] = "0";
						}
					}
					getrange (ao->a[0]);
					getrange (ao->a[1]);
					getrange (ao->a[2]);
					if (ao->a[0] && ao->a[1]) {
						char rn[8];
						strncpy (rn, ao->a[1], 7);
						int r0 = getreg (ao->a[0]);
						int r1 = getreg (ao->a[1]);
						if ((r0 < 0 || r0 > 15) || (r1 > 15 || r1 < 0)) {
							return 0;
						}
						ao->o |= r0 << 20;
						if (!strcmp (ops[i].name, "strd")) {
							r1 = getreg (ao->a[2]);
							if (r1 == -1) {
								break;
							}
							ao->o |= r1 << 8;
							if (ao->a[3]) {
								char *bracket = strchr (ao->a[3], ']');
								if (bracket) {
									*bracket = '\0';
								}
								int num = getnum (ao->a[3]);
								ao->o |= (num & 0x0f) << 24;
								ao->o |= ((num >> 4) & 0x0f) << 16;
							}
							break;
						}
						if (!strcmp (ops[i].name, "strh")) {
							ao->o |= r1 << 8;
							if (ao->a[2]) {
								reg = getreg (ao->a[2]);
								if (reg != -1) {
									ao->o |= reg << 24;
								} else {
									ao->o |= 1 << 14;
									ao->o |= getnum (ao->a[2]) << 24;
								}
							} else {
								ao->o |= 1 << 14;
							}
							break;
						}
						if (rex) {
							ao->o |= r1 << 24;
						} else {
							ao->o |= r1 << 8; // delta
						}
					} else {
						return 0;
					}

					ret = getreg (ao->a[2]);
					if (ret != -1) {
						if (rex) {
							ao->o |= 1;
							ao->o |= (ret & 0x0f) << 8;
						} else {
							ao->o |= (strstr (str, "],")) ? 6 : 7;
							ao->o |= (ret & 0x0f) << 24;
						}
						if (ao->a[3]) {
							shift = getshift (ao->a[3]);
							low = shift & 0xFF;
							high = shift & 0xFF00;
							ao->o |= low << 24;
							ao->o |= high << 8;
						}
					} else {
						int num = getnum (ao->a[2]) & 0xfff;
						if (err) {
							break;
						}
						if (rex) {
							ao->o |= 1;
						} else {
							ao->o |= (strstr (str, "],")) ? 4 : 5;
						}
						ao->o |= 1;
						ao->o |= (num & 0xff) << 24;
						ao->o |= ((num >> 8) & 0xf) << 16;
					}

					break;
				case TYPE_IMM:
					if (*ao->a[0]++ == '{') {
						for (j = 0; j < 16; j++) {
							if (ao->a[j] && *ao->a[j]) {
								getrange (ao->a[j]); // XXX filter regname string
								reg = getreg (ao->a[j]);
								if (reg != -1) {
									if (reg < 8) {
										ao->o |= 1 << (24 + reg);
									} else {
										ao->o |= 1 << (8 + reg);
									}
								}
							}
						}
					} else {
						ao->o |= getnum (ao->a[0]) << 24; // ???
					}
					break;
				case TYPE_BRA:
					if ((ret = getreg (ao->a[0])) == -1) {
						// TODO: control if branch out of range
						ret = (getnum (ao->a[0]) - (int)ao->off - 8) / 4;
						if (ret >= 0x00800000 || ret < (int)0xff800000) {
							eprintf ("Branch into out of range\n");
							return 0;
						}
						ao->o |= ((ret >> 16) & 0xff) << 8;
						ao->o |= ((ret >> 8) & 0xff) << 16;
						ao->o |= ((ret)&0xff) << 24;
					} else {
						eprintf ("This branch does not accept reg as arg\n");
						return 0;
					}
					break;
				case TYPE_BKP:
					ao->o |= 0x70 << 24;
					if (ao->a[0]) {
						int n = getnum (ao->a[0]);
						ao->o |= ((n & 0xf) << 24);
						ao->o |= (((n >> 4) & 0xff) << 16);
					}
					break;
				case TYPE_BRR:
					if ((ret = getreg (ao->a[0])) == -1) {
						ut32 dst = getnum (ao->a[0]);
						dst -= (ao->off + 8);
						if (dst & 0x2) {
							ao->o = 0xfb;
						} else {
							ao->o = 0xfa;
						}
						dst /= 4;
						ao->o |= ((dst >> 16) & 0xff) << 8;
						ao->o |= ((dst >> 8) & 0xff) << 16;
						ao->o |= ((dst)&0xff) << 24;
						return 4;
					} else {
						ao->o |= (getreg (ao->a[0]) << 24);
					}
					break;
				case TYPE_HLT: {
					ut32 o = 0, n = getnum (ao->a[0]);
					o |= ((n >> 12) & 0xf) << 8;
					o |= ((n >> 8) & 0xf) << 20;
					o |= ((n >> 4) & 0xf) << 16;
					o |= ((n) & 0xf) << 24;
					ao->o |=o;
				}
				break;
			case TYPE_SWI:
				ao->o |= (getnum (ao->a[0]) & 0xff) << 24;
				ao->o |= ((getnum (ao->a[0]) >> 8) & 0xff) << 16;
				ao->o |= ((getnum (ao->a[0]) >> 16) & 0xff) << 8;
				break;
			case TYPE_UDF:
				{
					// e7f000f0 = udf 0
					// e7ffffff = udf 0xffff
					ut32 n = getnum (ao->a[0]);
					ao->o |= 0xe7;
					ao->o |= (n & 0xf) << 24;
					ao->o |= ((n >> 4) & 0xff) << 16;
					ao->o |= ((n >> 12) & 0xf) << 8;
				}
				break;
			case TYPE_ARI:
				if (!ao->a[2]) {
					ao->a[2] = ao->a[1];
					ao->a[1] = ao->a[0];
				}
				reg = getreg (ao->a[0]);
				if (reg == -1) {
					return 0;
				}
				ao->o |= reg << 20;

				reg = getreg (ao->a[1]);
				if (reg == -1) {
					return 0;
				}
				ao->o |= reg << 8;
				reg = getreg (ao->a[2]);
				ao->o |= (reg != -1)? reg << 24 : 2 | getnum (ao->a[2]) << 24;
				if (ao->a[3]) {
					ao->o |= getshift (ao->a[3]);
				}
				break;
			case TYPE_SWP:
				{
				int a1 = getreg (ao->a[1]);
				if (a1) {
					ao->o = 0xe1;
					ao->o |= (getreg (ao->a[0]) << 4) << 16;
					ao->o |= (0x90 + a1) << 24;
					if (ao->a[2]) {
						ao->o |= (getreg (ao->a[2] + 1)) << 8;
					} else {
						return 0;
					}
				}
				if (0xff == ((ao->o >> 16) & 0xff)) {
					return 0;
				}
				}
				break;
			case TYPE_MOV:
				if (!strcmpnull (ao->op, "movs")) {
					ao->o = 0xb0e1;
				}
				ao->o |= getreg (ao->a[0]) << 20;
				ret = getreg (ao->a[1]);
				if (ret != -1) {
					ao->o |= ret << 24;
				} else {
					int immed = getimmed8 (ao->a[1]);
					if (err) {
						return 0;
					}
					ao->o |= 0xa003 | (immed & 0xff) << 24 | (immed >> 8) << 16;
				}
				break;
			case TYPE_MOVW:
				reg = getreg (ao->a[0]);
				if (reg == -1) {
					return 0;
				}
				ao->o |= getreg (ao->a[0]) << 20;
				ret = getnum (ao->a[1]);

				ao->o |= 0x3 | ret << 24;
				ao->o |= (ret & 0xf000) >> 4;
				ao->o |= (ret & 0xf00) << 8;
				break;
			case TYPE_MOVT:
				ao->o |= getreg (ao->a[0]) << 20;
				ret = getnum (ao->a[1]);

				ao->o |= 0x4003 | ret << 24;
				ao->o |= (ret & 0xf000) >> 4;
				ao->o |= (ret & 0xf00) << 8;
				break;
			case TYPE_MUL:
				if (!strcmpnull (ao->op, "mul")) {
					ret = getreg (ao->a[0]);
					a = getreg (ao->a[1]);
					b = getreg (ao->a[2]);
					if (b == -1) {
						b = a;
						a = ret;
					}
					if (ret == -1 || a == -1) {
						return 0;
					}
					ao->o |= ret << 8;
					ao->o |= a << 24;
					ao->o |= b << 16;
				} else {
					low = getreg (ao->a[0]);
					high = getreg (ao->a[1]);
					a = getreg (ao->a[2]);
					b = getreg (ao->a[3]);
					if (low == -1 || high == -1 || a == -1 || b == -1) {
						return 0;
					}
					if (!strcmpnull (ao->op, "smlal")) {
						ao->o |= low << 20;
						ao->o |= high << 8;
						ao->o |= a << 24;
						ao->o |= b << 16;
					} else if (!strncmp (ao->op, "smla", 4)) {
						if (low > 14 || high > 14 || a > 14) {
							return 0;
						}
						ao->o |= low << 8;
						ao->o |= high << 24;
						ao->o |= a << 16;
						ao->o |= b << 20;
						break;
					} else {
						ao->o |= low << 20;
						ao->o |= high << 8;
						ao->o |= a << 24;
						ao->o |= b << 16;
					}
				}
				break;
			case TYPE_TST:
				a = getreg (ao->a[0]);
				b = getreg (ao->a[1]);
				if (b == -1) {
					int y, z;
					b = getnum (ao->a[1]);
					if (b >= 0 && b <= 0xff) {
						ao->o = 0x50e3;
						// TODO: if (b>255) -> automatic multiplier
						ao->o |= (a << 8);
						ao->o |= ((b & 0xff) << 24);
					} else
					if (findyz (b, &y, &z)) {
						ao->o = 0x50e3;
						ao->o |= (y << 24);
						ao->o |= (z << 16);
					} else {
						eprintf ("Parameter %d out0x3000a0e1 of range (0-255)\n", (int)b);
						return 0;
					}
				} else {
					ao->o |= (a << 8);
					ao->o |= (b << 24);
					if (ao->a[2]) {
						ao->o |= getshift (ao->a[2]);
					}
				}
				if (ao->a[2]) {
					int n = getnum (ao->a[2]);
					if (n & 1) {
						eprintf ("Invalid multiplier\n");
						return 0;
					}
					ao->o |= (n >> 1) << 16;
				}
				break;
			case TYPE_SHFT:
				reg = getreg (ao->a[2]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 16;

				reg = getreg (ao->a[0]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 20;

				reg = getreg (ao->a[1]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 24;
				break;
			case TYPE_REV:
				reg = getreg (ao->a[0]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 20;

				reg = getreg (ao->a[1]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 24;

				break;
			case TYPE_ENDIAN:
				if (!strcmp (ao->a[0], "le")) {
					ao->o |= 0;
				} else if (!strcmp (ao->a[0], "be")) {
					ao->o |= 0x20000;
				} else {
					return 0;
				}
				break;
			case TYPE_COPROC:
				//printf ("%s %s %s %s %s\n", ao->a[0], ao->a[1], ao->a[2], ao->a[3], ao->a[4] );
				if (ao->a[0]) {
					coproc = getnum (ao->a[0] + 1);
					if (coproc == -1 || coproc > 9) {
						return 0;
					}
					ao->o |= coproc << 16;
				}

				opc = getnum (ao->a[1]);
				if (opc == -1 || opc > 7) {
					return 0;
				}
				ao->o |= opc << 13;

				reg = getreg (ao->a[2]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 20;

				// coproc register 1
				const char *a3 = ao->a[3];
				if (a3) {
					coproc = getnum (a3 + 1);
					if (coproc == -1 || coproc > 15) {
						return 0;
					}
					ao->o |= coproc << 8;
				}

				const char *a4 = ao->a[4];
				if (a4) {
					coproc = getnum (ao->a[4] + 1);
					if (coproc == -1 || coproc > 15) {
						return 0;
					}
					ao->o |= coproc << 24;
				}

				coproc = getnum (ao->a[5]);
				if (coproc > -1) {
					if (coproc > 7) {
						return 0;
					}
					// optional opcode
					ao->o |= coproc << 29;
				}

				break;
			case TYPE_CLZ:
				ao->o |= 1 << 28;

				reg = getreg (ao->a[0]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 20;

				reg = getreg (ao->a[1]);
				if (reg == -1 || reg > 14) {
					return 0;
				}
				ao->o |= reg << 24;

				break;
			}
			}
			return 1;
		}
	}
	return 0;
}