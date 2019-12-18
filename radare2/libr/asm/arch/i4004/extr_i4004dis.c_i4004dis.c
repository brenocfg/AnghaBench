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
typedef  int const ut16 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;

/* Variables and functions */
 char** i4004_e ; 
 char** i4004_f ; 
 int i4004_get_ins_len (int const) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char const*) ; 
 char* sdb_fmt (char*,int const,...) ; 

__attribute__((used)) static int i4004dis (RAsmOp *op, const ut8 *buf, int len) {
	int rlen = i4004_get_ins_len (*buf);
	ut8 high = (*buf & 0xf0) >> 4;
	ut8 low = (*buf & 0xf);
	const char *buf_asm = "invalid";
	if (rlen > len)	{
		return op->size = 0;
	}
	switch (high) {
	case 0: buf_asm = low? "invalid": "nop"; break;
	case 1: buf_asm = sdb_fmt ("jcn %d 0x%02x", low, buf[1]); break;
	case 2:
		if (rlen == 1) {
			buf_asm = sdb_fmt ("src r%d", (low & 0xe));
		} else {
			buf_asm = sdb_fmt ("fim r%d, 0x%02x", (low & 0xe), buf[1]);
		}
		break;
	case 3:
		if ((low & 1) == 1) {
			buf_asm = sdb_fmt ("jin r%d", (low & 0xe));
		} else {
			buf_asm = sdb_fmt ("fin r%d", (low & 0xe));
		}
		break;
	case 4: buf_asm = sdb_fmt ("jun 0x%03x", ((ut16)(low<<8) | buf[1])); break;
	case 5: buf_asm = sdb_fmt ("jms 0x%03x", ((ut16)(low<<8) | buf[1])); break;
	case 6: buf_asm = sdb_fmt ("inc r%d", low); break;
	case 7: buf_asm = sdb_fmt ("isz r%d, 0x%02x", low, buf[1]); break;
	case 8: buf_asm = sdb_fmt ("add r%d", low); break;
	case 9: buf_asm = sdb_fmt ("sub r%d", low); break;
	case 10: buf_asm = sdb_fmt ("ld r%d", low); break;
	case 11: buf_asm = sdb_fmt ("xch r%d", low); break;
	case 12: buf_asm = sdb_fmt ("bbl %d", low); break;
	case 13: buf_asm = sdb_fmt ("ldm %d", low); break;
	case 14: buf_asm = i4004_e[low]; break;
	case 15: buf_asm = i4004_f[low]; break;
	}
	r_strbuf_set (&op->buf_asm, buf_asm);
	return op->size = rlen;
}