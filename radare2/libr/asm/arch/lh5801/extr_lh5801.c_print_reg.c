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
struct lh5801_insn_desc {int format; } ;
struct lh5801_insn {size_t type; int opcode; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  LH5801_IFMT_AREG 134 
 int LH5801_IFMT_FD_MOD ; 
#define  LH5801_IFMT_PREG 133 
 int LH5801_IFMT_REG_MASK ; 
#define  LH5801_IFMT_RFULL 132 
#define  LH5801_IFMT_RHIGH 131 
#define  LH5801_IFMT_RLOW 130 
#define  LH5801_IFMT_RMEM 129 
 int LH5801_IFMT_RMODE (int) ; 
#define  LH5801_IFMT_SREG 128 
 struct lh5801_insn_desc* lh5801_insn_descs ; 

__attribute__((used)) static char *print_reg(char *buf, const struct lh5801_insn *insn) {
	const struct lh5801_insn_desc desc = lh5801_insn_descs[insn->type];
	unsigned regnr = (insn->opcode >> 4) & 3;
	const char names[] = "xyu";
	char *saved_buf = buf;

	/* Handle A, S, and P, before handling R */
	switch(desc.format & LH5801_IFMT_REG_MASK) {
		case LH5801_IFMT_AREG: return "a";
		case LH5801_IFMT_SREG: return "s";
		case LH5801_IFMT_PREG: return "p";
	}

	if (regnr == 3)
		return "invalid";
	else switch (LH5801_IFMT_RMODE(desc.format)) {
	case LH5801_IFMT_RFULL:
		buf[0] = names[regnr];
		buf[1] = '\0';
		break;
	case LH5801_IFMT_RLOW:
	case LH5801_IFMT_RHIGH:
		buf[0] = names[regnr];
		buf[1] = (desc.format & LH5801_IFMT_RLOW)? 'l':'h';
		buf[2] = '\0';
		break;
	case LH5801_IFMT_RMEM:
		if (desc.format & LH5801_IFMT_FD_MOD) {
			if (insn->fd)
				*(buf++) = '#';
			buf[0] = '(';
			buf[1] = names[regnr];
			buf[2] = ')';
			buf[3] = '\0';
		} else {
			return NULL;
		}
		break;
	default:
		return NULL;
	}
	return saved_buf;
}