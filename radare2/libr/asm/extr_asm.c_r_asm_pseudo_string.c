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
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;

/* Variables and functions */
 int r_str_unescape (char*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int r_asm_pseudo_string(RAsmOp *op, char *input, int zero) {
	int len = strlen (input) - 1;
	if (len < 1) {
		return 0;
	}
	// TODO: if not starting with '"'.. give up
	if (input[len] == '"') {
		input[len] = 0;
	}
	if (*input == '"') {
		input++;
	}
	len = r_str_unescape (input) + zero;
	r_strbuf_set (&op->buf, input); // uh?
	return len;
}