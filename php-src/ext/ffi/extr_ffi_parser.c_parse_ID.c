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

/* Variables and functions */
 int YY_ID ; 
 int get_sym () ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 size_t yy_pos ; 
 size_t yy_text ; 

__attribute__((used)) static int parse_ID(int sym, const char **name, size_t *name_len) {
	if (sym != YY_ID) {
		yy_error_sym("<ID> expected, got", sym);
	}
	*name = (const char*)yy_text; *name_len = yy_pos - yy_text;
	sym = get_sym();
	return sym;
}