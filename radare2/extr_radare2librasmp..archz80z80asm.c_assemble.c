#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  file; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int A ; 
#define  AF 229 
 int A_I ; 
 int A_NN ; 
 int A_R ; 
 int C ; 
#define  DE 228 
 int HL ; 
 int SPHL ; 
 int SPNN ; 
#define  Z80_ADC 227 
#define  Z80_ADD 226 
#define  Z80_AND 225 
#define  Z80_BIT 224 
#define  Z80_CALL 223 
#define  Z80_CCF 222 
#define  Z80_CP 221 
#define  Z80_CPD 220 
#define  Z80_CPDR 219 
#define  Z80_CPI 218 
#define  Z80_CPIR 217 
#define  Z80_CPL 216 
#define  Z80_DAA 215 
#define  Z80_DB 214 
#define  Z80_DEC 213 
#define  Z80_DEFB 212 
#define  Z80_DEFM 211 
#define  Z80_DEFS 210 
#define  Z80_DEFW 209 
#define  Z80_DI 208 
#define  Z80_DJNZ 207 
#define  Z80_DM 206 
#define  Z80_DS 205 
#define  Z80_DW 204 
#define  Z80_EI 203 
#define  Z80_ELSE 202 
#define  Z80_END 201 
#define  Z80_ENDIF 200 
#define  Z80_ENDM 199 
#define  Z80_EX 198 
#define  Z80_EXX 197 
#define  Z80_HALT 196 
#define  Z80_IF 195 
#define  Z80_IM 194 
#define  Z80_IN 193 
#define  Z80_INC 192 
#define  Z80_IND 191 
#define  Z80_INDR 190 
#define  Z80_INI 189 
#define  Z80_INIR 188 
#define  Z80_JP 187 
#define  Z80_JR 186 
#define  Z80_LD 185 
#define  Z80_LDD 184 
#define  Z80_LDDR 183 
#define  Z80_LDI 182 
#define  Z80_LDIR 181 
#define  Z80_NEG 180 
#define  Z80_NOP 179 
#define  Z80_OR 178 
#define  Z80_ORG 177 
#define  Z80_OTDR 176 
#define  Z80_OTIR 175 
#define  Z80_OUT 174 
#define  Z80_OUTD 173 
#define  Z80_OUTI 172 
#define  Z80_POP 171 
#define  Z80_PUSH 170 
#define  Z80_RES 169 
#define  Z80_RET 168 
#define  Z80_RETI 167 
#define  Z80_RETN 166 
#define  Z80_RL 165 
#define  Z80_RLA 164 
#define  Z80_RLC 163 
#define  Z80_RLCA 162 
#define  Z80_RLD 161 
#define  Z80_RR 160 
#define  Z80_RRA 159 
#define  Z80_RRC 158 
#define  Z80_RRCA 157 
#define  Z80_RRD 156 
#define  Z80_RST 155 
#define  Z80_SBC 154 
#define  Z80_SCF 153 
#define  Z80_SEEK 152 
#define  Z80_SET 151 
#define  Z80_SLA 150 
#define  Z80_SLI 149 
#define  Z80_SRA 148 
#define  Z80_SRL 147 
#define  Z80_SUB 146 
#define  Z80_XOR 145 
 int _NN ; 
 int addHL ; 
 int addr ; 
 int baseaddr ; 
 scalar_t__ comma ; 
 int /*<<< orphan*/  define_macro ; 
 char* delspc (char const*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  has_argument (char const**) ; 
 scalar_t__ indexed ; 
 scalar_t__ indexjmp ; 
#define  ldA 144 
#define  ldB 143 
#define  ldBC 142 
#define  ldC 141 
#define  ldD 140 
#define  ldDE 139 
#define  ldE 138 
#define  ldH 137 
#define  ldHL 136 
#define  ldI 135 
#define  ldL 134 
#define  ldR 133 
#define  ldSP 132 
#define  ld_BC 131 
#define  ld_DE 130 
#define  ld_HL 129 
#define  ld_NN 128 
 int ld_nnA ; 
 int ld_nnHL ; 
 unsigned char* obuf ; 
 int obuflen ; 
 int rd_0_2 (char const**) ; 
 int /*<<< orphan*/  rd_0_7 (char const**) ; 
 int /*<<< orphan*/  rd_a (char const**) ; 
 int rd_a_hl (char const**) ; 
 int /*<<< orphan*/  rd_af_ (char const**) ; 
 int /*<<< orphan*/  rd_byte (char const**,char) ; 
 int /*<<< orphan*/  rd_c (char const**) ; 
 int rd_cc (char const**) ; 
 int /*<<< orphan*/  rd_character (char const**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rd_comma (char const**) ; 
 int rd_ex1 (char const**) ; 
 int rd_expr (char const**,char,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  rd_hl (char const**) ; 
 int /*<<< orphan*/  rd_hlx (char const**) ; 
 int rd_in (char const**) ; 
 int rd_jp (char const**) ; 
 int rd_jr (char const**) ; 
 int rd_ld (char const**) ; 
 int rd_ld_hl (char const**) ; 
 int rd_ld_nn (char const**) ; 
 int rd_lda (char const**) ; 
 int rd_ldbcdehla (char const**) ; 
 int rd_nn_nn (char const**) ; 
 int rd_nnc (char const**) ; 
 int rd_out (char const**) ; 
 int rd_r (char const**) ; 
 int rd_r_ (char const**) ; 
 int rd_r_add (char const**) ; 
 int rd_r_rr (char const**) ; 
 int rd_rr_ (char const**) ; 
 int rd_rrxx (char const**) ; 
 int rd_sp (char const**) ; 
 int rd_stack (char const**) ; 
 int rd_word (char const**,char) ; 
 scalar_t__ readbyte ; 
 int readcommand (char const**) ; 
 int /*<<< orphan*/  readlabel (char const**,int) ; 
 scalar_t__ readword ; 
 int /*<<< orphan*/  skipword (char const**,char) ; 
 size_t sp ; 
 TYPE_1__* stack ; 
 char* strchr (char*,char) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  write_one_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ writebyte ; 
 int /*<<< orphan*/  wrtb (int) ; 
 void* z80buffer ; 

__attribute__((used)) static int assemble(const char *str, unsigned char *_obuf) {
	int ifcount = 0, noifcount = 0;
	const char *ptr;
	char *bufptr;
	int r, s;			/* registers */

	obuflen = 0;
	obuf = _obuf;
	/* continue assembling until the last input file is done */
	// for (file = 0; file < infilecount; ++file)
	do {
		int cmd, cont = 1;
		// XXX: must free
		z80buffer = strdup (str);
		if (!cont) {
			break;		/* break to next source file */
		}
		// if (havelist)
		// fprintf (listfile, "%04x", addr);
		for (bufptr = z80buffer; (bufptr = strchr (bufptr, '\n'));) {
			*bufptr = ' ';
		}
		for (bufptr = z80buffer; (bufptr = strchr (bufptr, '\r'));) {
			*bufptr = ' ';
		}
		ptr = z80buffer;
		// lastlabel = NULL;
		baseaddr = addr;
		++stack[sp].line;
		ptr = delspc (ptr);
		if (!*ptr) {
			continue;
		}
		if (!noifcount && !define_macro) {
			readlabel (&ptr, 1);
		} else {
			readlabel (&ptr, 0);
		}
		ptr = delspc (ptr);
		if (!*ptr) {
			continue;
		}
		comma = 0;
		indexed = 0;
		indexjmp = 0;
		writebyte = 0;
		readbyte = 0;
		readword = 0;
		cmd = readcommand (&ptr) - 1;
		int i, have_quote;
		switch (cmd) {
		case Z80_ADC:
			if (!(r = rd_a_hl (&ptr))) {
				break;
			}
			if (r == HL) {
				if (!(r = rd_rr_(&ptr))) {
					break;
				}
				wrtb (0xED);
				wrtb (0x4A + 0x10 * --r);
				break;
			}
			if (!(r = rd_r (&ptr))) {
				break;
			}
			wrtb (0x88 + --r);
			break;
		case Z80_ADD:
			if (!(r = rd_r_add (&ptr))) {
				break;
			}
			if (r == addHL) {
				if (!(r = rd_rrxx (&ptr))) {
					break;
				}
				wrtb (0x09 + 0x10 * --r);		/* ADD HL/IX/IY, qq  */
				break;
			}
			if (has_argument (&ptr)) {
				if (r != A) {
					eprintf ("parse error before: %s\n", ptr);
					break;
				}
				if (!(r = rd_r (&ptr))) {
					break;
				}
				wrtb (0x80 + --r);		/* ADD A,r  */
				break;
			}
			wrtb (0x80 + --r);		/* ADD r  */
			break;
		case Z80_AND:
			if (!(r = rd_r (&ptr))) {
				break;
			}
			wrtb (0xA0 + --r);
			break;
		case Z80_BIT:
			if (!rd_0_7 (&ptr)) {
				break;
			}
			rd_comma (&ptr);
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x40 + (r - 1));
			break;
		case Z80_CALL:
			if ((r = rd_cc (&ptr))) {
				wrtb (0xC4 + 8 * --r);
				rd_comma (&ptr);
			} else {
				wrtb (0xCD);
			}
			break;
		case Z80_CCF:
			wrtb (0x3F);
			break;
		case Z80_CP:
			if (!(r = rd_r (&ptr))) {
				break;
			}
			wrtb (0xB8 + --r);
			break;
		case Z80_CPD:
			wrtb (0xED);
			wrtb (0xA9);
			break;
		case Z80_CPDR:
			wrtb (0xED);
			wrtb (0xB9);
			break;
		case Z80_CPI:
			wrtb (0xED);
			wrtb (0xA1);
			break;
		case Z80_CPIR:
			wrtb (0xED);
			wrtb (0xB1);
			break;
		case Z80_CPL:
			wrtb (0x2F);
			break;
		case Z80_DAA:
			wrtb (0x27);
			break;
		case Z80_DEC:
			if (!(r = rd_r_rr (&ptr))) {
				break;
			}
			if (r < 0) {
				wrtb (0x05 - 8 * ++r);
				break;
			}
			wrtb (0x0B + 0x10 * --r);
			break;
		case Z80_DI:
			wrtb (0xF3);
			break;
		case Z80_DJNZ:
			wrtb (0x10);
			// rd_wrt_jr (&ptr, '\0');
			break;
		case Z80_EI:
			wrtb (0xFB);
			break;
		case Z80_EX:
			if (!(r = rd_ex1 (&ptr))) {
				break;
			}
			switch (r) {
			case DE:
				if (!rd_hl (&ptr)) {
					break;
				}
				wrtb (0xEB);
				break;
			case AF:
				if (!rd_af_(&ptr)) {
					break;
				}
				wrtb (0x08);
				break;
			default:
				if (!rd_hlx (&ptr)) {
					break;
				}
				wrtb (0xE3);
			}
			break;
		case Z80_EXX:
			wrtb (0xD9);
			break;
		case Z80_HALT:
			wrtb (0x76);
			break;
		case Z80_IM:
			if (!(r = rd_0_2 (&ptr))) {
				break;
			}
			wrtb (0xED);
			wrtb (0x46 + 8 * --r);
			break;
		case Z80_IN:
			if (!(r = rd_in (&ptr))) {
				break;
			}
			if (r == A) {
				if (!(r = rd_nnc (&ptr))) {
					break;
				}
				if (r == C) {
					wrtb (0xED);
					wrtb (0x40 + 8 * (A - 1));
					break;
				}
				wrtb (0xDB);
				break;
			}
			if (!rd_c (&ptr)) {
				break;
			}
			wrtb (0xED);
			wrtb (0x40 + 8 * --r);
			break;
		case Z80_INC:
			if (!(r = rd_r_rr (&ptr))) {
				break;
			}
			if (r < 0) {
				wrtb (0x04 - 8 * ++r);
				break;
			}
			wrtb (0x03 + 0x10 * --r);
			break;
		case Z80_IND:
			wrtb (0xED);
			wrtb (0xAA);
			break;
		case Z80_INDR:
			wrtb (0xED);
			wrtb (0xBA);
			break;
		case Z80_INI:
			wrtb (0xED);
			wrtb (0xA2);
			break;
		case Z80_INIR:
			wrtb (0xED);
			wrtb (0xB2);
			break;
		case Z80_JP:
			r = rd_jp (&ptr);
			if (r < 0) {
				wrtb (0xE9);
				break;
			}
			if (r) {
				wrtb (0xC2 + 8 * --r);
				rd_comma (&ptr);
			} else {
				wrtb (0xC3);
			}
			break;
		case Z80_JR:
			r = rd_jr (&ptr);
			if (r) {
				rd_comma (&ptr);
			}
			wrtb (0x18 + 8 * r);
			break;
		case Z80_LD:
			if (!(r = rd_ld (&ptr))) {
				break;
			}
			switch (r) {
			case ld_BC:
			case ld_DE:
				if (!rd_a (&ptr)) {
					break;
				}
				wrtb (0x02 + 0x10 * (r == ld_DE));
				break;
			case ld_HL:
				r = rd_ld_hl (&ptr);
				wrtb (0x70 + --r);
				break;
			case ld_NN:
				if (!(r = rd_ld_nn (&ptr))) {
					break;
				}
				if (r == ld_nnA || r == ld_nnHL) {
					wrtb (0x22 + 0x10 * (r == ld_nnA));
					break;
				}
				wrtb (0xED);
				wrtb (0x43 + 0x10 * --r);
				break;
			case ldA:
				if (!(r = rd_lda (&ptr))) {
					break;
				}
				if (r == A_NN) {
					wrtb (0x3A);
					break;
				}
				if (r == A_I || r == A_R) {
					wrtb (0xED);
					wrtb (0x57 + 8 * (r == A_R));
					break;
				}
				if (r < 0) {
					wrtb (0x0A - 0x10 * ++r);
					break;
				}
				wrtb (0x78 + --r);
				break;
			case ldB:
			case ldC:
			case ldD:
			case ldE:
			case ldH:
			case ldL:
				if (!(s = rd_ldbcdehla (&ptr))) {
					break;
				}
				wrtb (0x40 + 0x08 * (r - 7) + (s - 1));
				break;
			case ldBC:
			case ldDE:
				s = rd_nn_nn (&ptr);
				if (s == _NN) {
					wrtb (0xED);
					wrtb (0x4B + 0x10 * (r == ldDE));
					break;
				}
				wrtb (0x01 + (r == ldDE) * 0x10);
				break;
			case ldHL:
				r = rd_nn_nn (&ptr);
				wrtb (0x21 + (r == _NN) * 9);
				break;
			case ldI:
			case ldR:
				if (!rd_a (&ptr)) {
					break;
				}
				wrtb (0xED);
				wrtb (0x47 + 0x08 * (r == ldR));
				break;
			case ldSP:
				r = rd_sp (&ptr);
				if (r == SPHL) {
					wrtb (0xF9);
					break;
				}
				if (r == SPNN) {
					wrtb (0x31);
					break;
				}
				wrtb (0xED);
				wrtb (0x7B);
				break;
			}
			break;
		case Z80_LDD:
			wrtb (0xED);
			wrtb (0xA8);
			break;
		case Z80_LDDR:
			wrtb (0xED);
			wrtb (0xB8);
			break;
		case Z80_LDI:
			wrtb (0xED);
			wrtb (0xA0);
			break;
		case Z80_LDIR:
			wrtb (0xED);
			wrtb (0xB0);
			break;
		case Z80_NEG:
			wrtb (0xED);
			wrtb (0x44);
			break;
		case Z80_NOP:
			wrtb (0x00);
			break;
		case Z80_OR:
			if (!(r = rd_r (&ptr))) {
				break;
			}
			wrtb (0xB0 + --r);
			break;
		case Z80_OTDR:
			wrtb (0xED);
			wrtb (0xBB);
			break;
		case Z80_OTIR:
			wrtb (0xED);
			wrtb (0xB3);
			break;
		case Z80_OUT:
			if (!(r = rd_nnc (&ptr))) {
				break;
			}
			if (r == C) {
				if (!(r = rd_out (&ptr))) {
					break;
				}
				wrtb (0xED);
				wrtb (0x41 + 8 * --r);
				break;
			}
			if (!rd_a (&ptr)) {
				break;
			}
			wrtb (0xD3);
			break;
		case Z80_OUTD:
			wrtb (0xED);
			wrtb (0xAB);
			break;
		case Z80_OUTI:
			wrtb (0xED);
			wrtb (0xA3);
			break;
		case Z80_POP:
			if (!(r = rd_stack (&ptr))) {
				break;
			}
			wrtb (0xC1 + 0x10 * --r);
			break;
		case Z80_PUSH:
			if (!(r = rd_stack (&ptr))) {
				break;
			}
			wrtb (0xC5 + 0x10 * --r);
			break;
		case Z80_RES:
			if (!rd_0_7 (&ptr)) {
				break;
			}
			rd_comma (&ptr);
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x80 + --r);
			break;
		case Z80_RET:
			if (!(r = rd_cc (&ptr))) {
				wrtb (0xC9);
				break;
			}
			wrtb (0xC0 + 8 * --r);
			break;
		case Z80_RETI:
			wrtb (0xED);
			wrtb (0x4D);
			break;
		case Z80_RETN:
			wrtb (0xED);
			wrtb (0x45);
			break;
		case Z80_RL:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x10 + --r);
			break;
		case Z80_RLA:
			wrtb (0x17);
			break;
		case Z80_RLC:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x00 + --r);
			break;
		case Z80_RLCA:
			wrtb (0x07);
			break;
		case Z80_RLD:
			wrtb (0xED);
			wrtb (0x6F);
			break;
		case Z80_RR:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x18 + --r);
			break;
		case Z80_RRA:
			wrtb (0x1F);
			break;
		case Z80_RRC:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x08 + --r);
			break;
		case Z80_RRCA:
			wrtb (0x0F);
			break;
		case Z80_RRD:
			wrtb (0xED);
			wrtb (0x67);
			break;
		case Z80_RST:
			ptr = "";
			break;
		case Z80_SBC:
			if (!(r = rd_a_hl (&ptr))) {
				break;
			}
			if (r == HL) {
				if (!(r = rd_rr_(&ptr))) {
					break;
				}
				wrtb (0xED);
				wrtb (0x42 + 0x10 * --r);
				break;
			}
			if (!(r = rd_r (&ptr))) {
				break;
			}
			wrtb (0x98 + --r);
			break;
		case Z80_SCF:
			wrtb (0x37);
			break;
		case Z80_SET:
			if (!rd_0_7 (&ptr)) {
				break;
			}
			rd_comma (&ptr);
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0xC0 + --r);
			break;
		case Z80_SLA:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x20 + --r);
			break;
		case Z80_SLI:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x30 + --r);
			break;
		case Z80_SRA:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x28 + --r);
			break;
		case Z80_SRL:
			if (!(r = rd_r_(&ptr))) {
				break;
			}
			wrtb (0xCB);
			wrtb (0x38 + --r);
			break;
		case Z80_SUB:
			if (!(r = rd_r (&ptr))) {
				break;
			}
			if (has_argument (&ptr)) {		/* SUB A,r ?  */
				if (r != A) {
					eprintf ("parse error before: %s\n", ptr);
					break;
				}
				if (!(r = rd_r (&ptr))) {
					break;
				}
			}
			wrtb (0x90 + --r);
			break;
		case Z80_XOR:
			if (!(r = rd_r (&ptr))) {
				break;
			}
			wrtb (0xA8 + --r);
			break;
		case Z80_DEFB:
		case Z80_DB:
		case Z80_DEFM:
		case Z80_DM:
			ptr = delspc (ptr);
			while (1) {
				have_quote = (*ptr == '"' || *ptr == '\'');
				if (have_quote) {
					/* Read string.  */
					int quote = *ptr;
					++ptr;
					while (*ptr != quote) {
						write_one_byte (rd_character (&ptr, NULL, 1), 0);
						if (*ptr == 0) {
							eprintf ("end of line in quoted string\n");
							break;
						}
					}
					++ptr;
				} else {
					/* Read expression.  */
					skipword (&ptr, ',');
				}
				ptr = delspc (ptr);
				if (*ptr == ',') {
					++ptr;
					continue;
				}
				if (*ptr != 0) {
					eprintf ("junk in byte definition: %s\n", ptr);
				}
				break;
			}
			break;
		case Z80_DEFW:
		case Z80_DW:
			if (!(r = rd_word (&ptr, ','))) {
				eprintf ("No data for word definition\n");
				break;
			}
			while (1) {
				ptr = delspc (ptr);
				if (*ptr != ',') {
					break;
				}
				++ptr;
				if (!(r = rd_word (&ptr, ','))) {
					eprintf ("Missing expression in defw\n");
				}
			}
			break;
		case Z80_DEFS:
		case Z80_DS:
			r = rd_expr (&ptr, ',', NULL, sp, 1);
			if (r < 0) {
				eprintf ("ds should have its first argument >=0"
					" (not -0x%x)\n", -r);
				break;
			}
			ptr = delspc (ptr);
			if (*ptr) {
				rd_comma (&ptr);
				readbyte = 0;
				rd_byte (&ptr, '\0');
				writebyte = 0;
				break;
			}
			for (i = 0; i < r; i++) {
				write_one_byte (0, 0);
			}
			break;
		case Z80_END:
			break;
		case Z80_ORG:
			addr = rd_expr (&ptr, '\0', NULL, sp, 1) & 0xffff;
			break;
		case Z80_IF:
			if (rd_expr (&ptr, '\0', NULL, sp, 1)) {
				ifcount++;
			} else {
				noifcount++;
			}
			break;
		case Z80_ELSE:
			if (ifcount == 0) {
				eprintf ("else without if\n");
				break;
			}
			noifcount = 1;
			ifcount--;
			break;
		case Z80_ENDIF:
			if (noifcount == 0 && ifcount == 0) {
				eprintf ("endif without if\n");
				break;
			}
			if (noifcount) {
				noifcount--;
			} else {
				ifcount--;
			}
			break;
		case Z80_ENDM:
			if (stack[sp].file) {
				eprintf ("endm outside macro definition\n");
			}
			break;
		case Z80_SEEK:
			eprintf ("seek error\n");
			break;
		default:
			// eprintf ("command or comment expected (was %s)\n", ptr);
			return 0;
		}
	} while (false);
	// free (infile);
	return obuflen;
}