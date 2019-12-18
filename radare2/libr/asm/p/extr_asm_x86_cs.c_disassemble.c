#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_16__ {int size; scalar_t__* op_str; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_18__ {int bits; scalar_t__ syntax; scalar_t__* features; int /*<<< orphan*/  pc; } ;
struct TYPE_17__ {int size; char* buf_asm; } ;
typedef  TYPE_2__ RAsmOp ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_X86 ; 
 int CS_MODE_16 ; 
 int CS_MODE_32 ; 
 int CS_MODE_64 ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_OFF ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 int /*<<< orphan*/  CS_OPT_SYNTAX ; 
 int /*<<< orphan*/  CS_OPT_SYNTAX_ATT ; 
 int /*<<< orphan*/  CS_OPT_SYNTAX_INTEL ; 
 int /*<<< orphan*/  CS_OPT_SYNTAX_MASM ; 
 int /*<<< orphan*/  CS_OPT_UNSIGNED ; 
 scalar_t__ R_ASM_SYNTAX_ATT ; 
 scalar_t__ R_ASM_SYNTAX_JZ ; 
 scalar_t__ R_ASM_SYNTAX_MASM ; 
 int cd ; 
 int /*<<< orphan*/  check_features (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cs_close (int*) ; 
 scalar_t__ cs_disasm (int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 scalar_t__ cs_disasm_iter (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* cs_malloc (int) ; 
 int cs_open (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cs_option (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decompile_vm (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ n ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_2__*,char*) ; 
 char* r_strbuf_get (char**) ; 
 char* sdb_fmt (char*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	static int omode = 0;
	int mode, ret;
	ut64 off = a->pc;

	mode =  (a->bits == 64)? CS_MODE_64:
		(a->bits == 32)? CS_MODE_32:
		(a->bits == 16)? CS_MODE_16: 0;
	if (cd && mode != omode) {
		cs_close (&cd);
		cd = 0;
	}
	if (op) {
		op->size = 0;
	}
	omode = mode;
	if (cd == 0) {
		ret = cs_open (CS_ARCH_X86, mode, &cd);
		if (ret) {
			return 0;
		}
	}
	if (a->features && *a->features) {
		cs_option (cd, CS_OPT_DETAIL, CS_OPT_ON);
	} else {
		cs_option (cd, CS_OPT_DETAIL, CS_OPT_OFF);
	}
	// always unsigned immediates (kernel addresses)
	// maybe r2 should have an option for this too?
#if CS_API_MAJOR >= 4
	cs_option (cd, CS_OPT_UNSIGNED, CS_OPT_ON);
#endif
	if (a->syntax == R_ASM_SYNTAX_MASM) {
#if CS_API_MAJOR >= 4
		cs_option (cd, CS_OPT_SYNTAX, CS_OPT_SYNTAX_MASM);
#endif
	} else if (a->syntax == R_ASM_SYNTAX_ATT) {
		cs_option (cd, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);
	} else {
		cs_option (cd, CS_OPT_SYNTAX, CS_OPT_SYNTAX_INTEL);
	}
	if (!op) {
		return true;
	}
	op->size = 1;
	cs_insn *insn = NULL;
#if USE_ITER_API
	{
		size_t size = len;
		if (!insn || cd < 1) {
			insn = cs_malloc (cd);
		}
		if (!insn) {
			cs_free (insn, n);
			return 0;
		}
		memset (insn, 0, insn->size);
		insn->size = 1;
		n = cs_disasm_iter (cd, (const uint8_t**)&buf, &size, (uint64_t*)&off, insn);
	}
#else
	n = cs_disasm (cd, (const ut8*)buf, len, off, 1, &insn);
#endif
	if (op) {
		op->size = 0;
	}
	if (a->features && *a->features) {
		if (!check_features (a, insn)) {
			op->size = insn->size;
			r_asm_op_set_asm (op, "illegal");
		}
	}
	if (op->size == 0 && n > 0 && insn->size > 0) {
		char *ptrstr;
		op->size = insn->size;
		char *buf_asm = sdb_fmt ("%s%s%s",
				insn->mnemonic, insn->op_str[0]?" ":"",
				insn->op_str);
		ptrstr = strstr (buf_asm, "ptr ");
		if (ptrstr) {
			memmove (ptrstr, ptrstr + 4, strlen (ptrstr + 4) + 1);
		}
		r_asm_op_set_asm (op, buf_asm);
	} else {
		decompile_vm (a, op, buf, len);
	}
	if (a->syntax == R_ASM_SYNTAX_JZ) {
		char *buf_asm = r_strbuf_get (&op->buf_asm);
		if (!strncmp (buf_asm, "je ", 3)) {
			memcpy (buf_asm, "jz", 2);
		} else if (!strncmp (buf_asm, "jne ", 4)) {
			memcpy (buf_asm, "jnz", 3);
		}
	}
#if 0
	// [eax + ebx*4]  =>  [eax + ebx * 4]
	char *ast = strchr (op->buf_asm, '*');
	if (ast && ast > op->buf_asm) {
		ast--;
		if (ast[0] != ' ') {
			char *tmp = strdup (ast + 1);
			if (tmp) {
				ast[0] = ' ';
				if (tmp[0] && tmp[1] && tmp[1] != ' ') {
					strcpy (ast, " * ");
					strcpy (ast + 3, tmp + 1);
				} else {
					strcpy (ast + 1, tmp);
				}
				free (tmp);
			}
		}
	}
#endif
#if USE_ITER_API
	/* do nothing because it should be allocated once and freed in the_end */
#else
	if (insn) {
		cs_free (insn, n);
	}
#endif
	return op->size;
}