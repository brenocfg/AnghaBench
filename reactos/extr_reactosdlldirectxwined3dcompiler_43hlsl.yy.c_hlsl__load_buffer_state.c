#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  yy_input_file; int /*<<< orphan*/ * yy_buf_pos; int /*<<< orphan*/  yy_n_chars; } ;

/* Variables and functions */
 TYPE_1__* YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  hlsl_in ; 
 int /*<<< orphan*/ * yy_c_buf_p ; 
 int /*<<< orphan*/  yy_hold_char ; 
 int /*<<< orphan*/  yy_n_chars ; 
 int /*<<< orphan*/ * yytext_ptr ; 

__attribute__((used)) static void hlsl__load_buffer_state  (void)
{
    	(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
	(yytext_ptr) = (yy_c_buf_p) = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
	hlsl_in = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
	(yy_hold_char) = *(yy_c_buf_p);
}