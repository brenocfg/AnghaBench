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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RBinJavaObj ;

/* Variables and functions */
 int java_print_opcode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int,char*,int) ; 

int r_java_disasm(RBinJavaObj *obj, ut64 addr, const ut8 *bytes, int len, char *output, int outlen) {
	//r_cons_printf ("r_java_disasm (allowed %d): 0x%02x, 0x%0x.\n", outlen, bytes[0], addr);
	return java_print_opcode (obj, addr, bytes[0], bytes, len, output, outlen);
}