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
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int gb_reg_idx (char) ; 
 int r_num_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_str_replace_in (char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 char* strchr (char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static bool gb_parse_cb2 (ut8 *buf, const int minlen, char *buf_asm, ut8 base) {
	ut64 num;
	int i;
	char *p, *q;
	if ((i = strlen (buf_asm)) < minlen) {
		return false;
	}
	r_str_replace_in (buf_asm, (ut32)i, "[ ", "[", true);
	r_str_replace_in (buf_asm, (ut32)i, " ]", "]", true);
	r_str_replace_in (buf_asm, (ut32)i, ", ", ",", true);
	p = strchr (buf_asm, (int)' ');
	if (!p) {
		return false;
	}
	q = strchr (p, (int)',');
	if (!q) {
		return false;
	}
	q[0] = '\0';
	if (p[1] == '\0' || q[1] == '\0') {
		q[0] = ',';
		return false;
	}
	num = r_num_get (NULL, &p[1]);
	q[0] = ',';
	if (num > 7) {
		return false;
	}
	buf[0] = base + (ut8)num * 8;
	i = gb_reg_idx (q[1]);
	if (i != -1) {
		buf[0] |= (ut8)i;
		return true;
	}
	if (strlen (q + 1) < 4) {
		return false;
	}
	if (!strncmp (q + 1, "[hl]", 4)) {
		buf[0] |= 6;
		return true;
	}
	return false;
}