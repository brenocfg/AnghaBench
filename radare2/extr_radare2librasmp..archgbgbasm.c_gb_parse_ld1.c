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

/* Variables and functions */
 int gb_reg_idx (char) ; 
 int /*<<< orphan*/  r_str_do_until_token (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  r_str_replace_in (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  str_op ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static bool gb_parse_ld1 (ut8 *buf, const int minlen, char *buf_asm) {
	int i;
	r_str_replace_in (buf_asm, strlen (buf_asm), ", ", ",", true);
	if ((i = strlen (buf_asm)) < minlen) {
		return false;
	}
	r_str_do_until_token (str_op, buf_asm, '\0');
	if (buf_asm[4] == ',') {
		i = gb_reg_idx (buf_asm[3]);
		if (i == (-1)) {
			return false;
		}
		buf[0] = (ut8)(0x40 + (i * 8));
		if ((i = gb_reg_idx (buf_asm[5])) == (-1)) {
			return false;
		}
		buf[0] |= (ut8)i;
	} else if (!strncmp (buf_asm + 3, "[hl],", 5)) {
		if ((i = gb_reg_idx (buf_asm[8])) == (-1)) {
			return false;
		}
		buf[0] = 0x70 | (ut8)i;
	}
	return true;
}