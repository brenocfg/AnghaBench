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
 int YY_EOF ; 
 int /*<<< orphan*/  get_sym () ; 
 int parse_declarations (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yy_buf ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int yy_line ; 
 int /*<<< orphan*/  yy_pos ; 
 int /*<<< orphan*/  yy_text ; 

__attribute__((used)) static void parse(void) {
	int sym;

	yy_pos = yy_text = yy_buf;
	yy_line = 1;
	sym = parse_declarations(get_sym());
	if (sym != YY_EOF) {
		yy_error_sym("<EOF> expected, got", sym);
	}
}