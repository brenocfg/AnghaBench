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
typedef  int* xtensa_insnbuf ;

/* Variables and functions */

__attribute__((used)) static int
format_decoder (const xtensa_insnbuf insn)
{
	if ((insn[0] & 0x8) == 0 && (insn[1] & 0) == 0) {
		return 0; /* x24 */
	}
	if ((insn[0] & 0xc) == 0x8 && (insn[1] & 0) == 0) {
		return 1; /* x16a */
	}
	if ((insn[0] & 0xe) == 0xc && (insn[1] & 0) == 0) {
		return 2; /* x16b */
	}
	if ((insn[0] & 0xf) == 0xe && (insn[1] & 0) == 0) {
		return 3; /* xt_format1 */
	}
	if ((insn[0] & 0xf) == 0xf && (insn[1] & 0x80000000) == 0) {
		return 4; /* xt_format2 */
	}
	return -1;
}