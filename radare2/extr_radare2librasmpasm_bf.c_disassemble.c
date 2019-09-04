#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char const*) ; 
 char* sdb_fmt (char const*,char const*,int) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	const ut8 *b;
	int rep = 1;

	/* Count repetitions of the current instruction, unless it's a trap. */
	if (*buf != 0x00 && *buf != 0xff) {
		for (b = &buf[1]; b < buf + len && *b == *buf; b++) {
			rep++;
		}
	}
	const char *buf_asm = "invalid";
	switch (*buf) {
	case '[':
		buf_asm = "while [ptr]";
		break;
	case ']':
		buf_asm = "loop";
		break;
	case '>':
		buf_asm = (rep > 1)? "add ptr": "inc ptr";
		break;
	case '<':
		buf_asm = (rep > 1)? "sub ptr": "dec ptr";
		break;
	case '+':
		buf_asm = (rep > 1)? "add [ptr]": "inc [ptr]";
		break;
	case '-':
		buf_asm = (rep > 1)? "sub [ptr]": "dec [ptr]";
		break;
	case ',':
		buf_asm = "in [ptr]";
		break;
	case '.':
		buf_asm = "out [ptr]";
		break;
	case 0xff:
	case 0x00:
		buf_asm = "trap";
		break;
	default:
		buf_asm = "nop";
		break;
	}

	if (rep > 1) {
		/* Note: snprintf's source and destination buffers may not
		* overlap. */
		const char *fmt = strchr (buf_asm, ' ')? "%s, %d": "%s %d";
		buf_asm = sdb_fmt (fmt, buf_asm, rep);
	}
	r_strbuf_set (&op->buf_asm, buf_asm);
	op->size = rep;
	return rep;
}