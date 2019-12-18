#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ vstr_t ;
struct TYPE_5__ {int hist_cur; char const* prompt; int /*<<< orphan*/  orig_line_len; int /*<<< orphan*/  cursor_pos; scalar_t__* escape_seq_buf; int /*<<< orphan*/  escape_seq; TYPE_1__* line; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESEQ_NONE ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_str (char const*) ; 
 int /*<<< orphan*/  readline_auto_indent () ; 
 TYPE_2__ rl ; 

void readline_init(vstr_t *line, const char *prompt) {
    rl.line = line;
    rl.orig_line_len = line->len;
    rl.escape_seq = ESEQ_NONE;
    rl.escape_seq_buf[0] = 0;
    rl.hist_cur = -1;
    rl.cursor_pos = rl.orig_line_len;
    rl.prompt = prompt;
    mp_hal_stdout_tx_str(prompt);
    #if MICROPY_REPL_AUTO_INDENT
    readline_auto_indent();
    #endif
}