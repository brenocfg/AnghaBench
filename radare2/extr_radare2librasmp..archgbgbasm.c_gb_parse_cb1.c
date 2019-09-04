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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int gb_reg_idx (char) ; 
 int /*<<< orphan*/  r_str_do_until_token (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  r_str_replace_in (char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  str_op ; 
 int const strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static bool gb_parse_cb1 (ut8 *buf, const int minlen, char *buf_asm, ut8 base) {
	int i;
	if (strlen (buf_asm) < minlen || minlen < 1) {
		return false;
	}
	buf[0] = base;
	char *ptr_asm = buf_asm + minlen - 1;
	i = strlen (ptr_asm);
	r_str_replace_in (ptr_asm, (ut32)i, "[ ", "[", true);
	r_str_replace_in (ptr_asm, (ut32)i, " ]", "]", true);
	r_str_do_until_token (str_op, buf_asm, ' ');
	i = gb_reg_idx (buf_asm[minlen - 1]);
	if (i != (-1)) {
		buf[0] |= (ut8)i;
		return true;
	}
	if (!strncmp (buf_asm, "[hl]", 4)) {
		buf[0] |= 6;
		return true;
	}
	return false;
}