#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ escape_seq; int orig_line_len; size_t cursor_pos; char* prompt; int* escape_seq_buf; int hist_cur; TYPE_1__* line; } ;
struct TYPE_9__ {size_t len; char* buf; } ;

/* Variables and functions */
 int CHAR_CTRL_A ; 
 int CHAR_CTRL_B ; 
 int CHAR_CTRL_C ; 
 int CHAR_CTRL_D ; 
 int CHAR_CTRL_E ; 
 int CHAR_CTRL_F ; 
 int CHAR_CTRL_K ; 
 int CHAR_CTRL_N ; 
 int CHAR_CTRL_P ; 
 int CHAR_CTRL_U ; 
 int /*<<< orphan*/  DEBUG_printf (char*,int,...) ; 
 scalar_t__ ESEQ_ESC ; 
 scalar_t__ ESEQ_ESC_BRACKET ; 
 scalar_t__ ESEQ_ESC_BRACKET_DIGIT ; 
 scalar_t__ ESEQ_ESC_O ; 
 scalar_t__ ESEQ_NONE ; 
 int /*<<< orphan*/ ** MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 scalar_t__ READLINE_HIST_SIZE ; 
 int /*<<< orphan*/  mp_hal_erase_line_from_cursor (size_t) ; 
 int /*<<< orphan*/  mp_hal_move_cursor_back (int) ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_str (char*) ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_strn (char*,int) ; 
 int /*<<< orphan*/  mp_plat_print ; 
 size_t mp_repl_autocomplete (char*,int,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  readline_hist ; 
 int /*<<< orphan*/  readline_push_history (scalar_t__) ; 
 TYPE_8__ rl ; 
 int /*<<< orphan*/  vstr_add_str (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vstr_cut_out_bytes (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vstr_cut_tail_bytes (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  vstr_ins_byte (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vstr_ins_char (TYPE_1__*,size_t,int) ; 
 int vstr_len (TYPE_1__*) ; 
 scalar_t__ vstr_null_terminated_str (TYPE_1__*) ; 

int readline_process_char(int c) {
    size_t last_line_len = rl.line->len;
    int redraw_step_back = 0;
    bool redraw_from_cursor = false;
    int redraw_step_forward = 0;
    if (rl.escape_seq == ESEQ_NONE) {
        if (CHAR_CTRL_A <= c && c <= CHAR_CTRL_E && vstr_len(rl.line) == rl.orig_line_len) {
            // control character with empty line
            return c;
        } else if (c == CHAR_CTRL_A) {
            // CTRL-A with non-empty line is go-to-start-of-line
            goto home_key;
        #if MICROPY_REPL_EMACS_KEYS
        } else if (c == CHAR_CTRL_B) {
            // CTRL-B with non-empty line is go-back-one-char
            goto left_arrow_key;
        #endif
        } else if (c == CHAR_CTRL_C) {
            // CTRL-C with non-empty line is cancel
            return c;
        #if MICROPY_REPL_EMACS_KEYS
        } else if (c == CHAR_CTRL_D) {
            // CTRL-D with non-empty line is delete-at-cursor
            goto delete_key;
        #endif
        } else if (c == CHAR_CTRL_E) {
            // CTRL-E is go-to-end-of-line
            goto end_key;
        #if MICROPY_REPL_EMACS_KEYS
        } else if (c == CHAR_CTRL_F) {
            // CTRL-F with non-empty line is go-forward-one-char
            goto right_arrow_key;
        } else if (c == CHAR_CTRL_K) {
            // CTRL-K is kill from cursor to end-of-line, inclusive
            vstr_cut_tail_bytes(rl.line, last_line_len - rl.cursor_pos);
            // set redraw parameters
            redraw_from_cursor = true;
        } else if (c == CHAR_CTRL_N) {
            // CTRL-N is go to next line in history
            goto down_arrow_key;
        } else if (c == CHAR_CTRL_P) {
            // CTRL-P is go to previous line in history
            goto up_arrow_key;
        } else if (c == CHAR_CTRL_U) {
            // CTRL-U is kill from beginning-of-line up to cursor
            vstr_cut_out_bytes(rl.line, rl.orig_line_len, rl.cursor_pos - rl.orig_line_len);
            // set redraw parameters
            redraw_step_back = rl.cursor_pos - rl.orig_line_len;
            redraw_from_cursor = true;
        #endif
        } else if (c == '\r') {
            // newline
            mp_hal_stdout_tx_str("\r\n");
            readline_push_history(vstr_null_terminated_str(rl.line) + rl.orig_line_len);
            return 0;
        } else if (c == 27) {
            // escape sequence
            rl.escape_seq = ESEQ_ESC;
        } else if (c == 8 || c == 127) {
            // backspace/delete
            if (rl.cursor_pos > rl.orig_line_len) {
                // work out how many chars to backspace
                #if MICROPY_REPL_AUTO_INDENT
                int nspace = 0;
                for (size_t i = rl.orig_line_len; i < rl.cursor_pos; i++) {
                    if (rl.line->buf[i] != ' ') {
                        nspace = 0;
                        break;
                    }
                    nspace += 1;
                }
                if (nspace < 4) {
                    nspace = 1;
                } else {
                    nspace = 4;
                }
                #else
                int nspace = 1;
                #endif

                // do the backspace
                vstr_cut_out_bytes(rl.line, rl.cursor_pos - nspace, nspace);
                // set redraw parameters
                redraw_step_back = nspace;
                redraw_from_cursor = true;
            }
        #if MICROPY_HELPER_REPL
        } else if (c == 9) {
            // tab magic
            const char *compl_str;
            size_t compl_len = mp_repl_autocomplete(rl.line->buf + rl.orig_line_len, rl.cursor_pos - rl.orig_line_len, &mp_plat_print, &compl_str);
            if (compl_len == 0) {
                // no match
            } else if (compl_len == (size_t)(-1)) {
                // many matches
                mp_hal_stdout_tx_str(rl.prompt);
                mp_hal_stdout_tx_strn(rl.line->buf + rl.orig_line_len, rl.cursor_pos - rl.orig_line_len);
                redraw_from_cursor = true;
            } else {
                // one match
                for (size_t i = 0; i < compl_len; ++i) {
                    vstr_ins_byte(rl.line, rl.cursor_pos + i, *compl_str++);
                }
                // set redraw parameters
                redraw_from_cursor = true;
                redraw_step_forward = compl_len;
            }
        #endif
        } else if (32 <= c && c <= 126) {
            // printable character
            vstr_ins_char(rl.line, rl.cursor_pos, c);
            // set redraw parameters
            redraw_from_cursor = true;
            redraw_step_forward = 1;
        }
    } else if (rl.escape_seq == ESEQ_ESC) {
        switch (c) {
            case '[':
                rl.escape_seq = ESEQ_ESC_BRACKET;
                break;
            case 'O':
                rl.escape_seq = ESEQ_ESC_O;
                break;
            default:
                DEBUG_printf("(ESC %d)", c);
                rl.escape_seq = ESEQ_NONE;
        }
    } else if (rl.escape_seq == ESEQ_ESC_BRACKET) {
        if ('0' <= c && c <= '9') {
            rl.escape_seq = ESEQ_ESC_BRACKET_DIGIT;
            rl.escape_seq_buf[0] = c;
        } else {
            rl.escape_seq = ESEQ_NONE;
            if (c == 'A') {
#if MICROPY_REPL_EMACS_KEYS
up_arrow_key:
#endif
                // up arrow
                if (rl.hist_cur + 1 < (int)READLINE_HIST_SIZE && MP_STATE_PORT(readline_hist)[rl.hist_cur + 1] != NULL) {
                    // increase hist num
                    rl.hist_cur += 1;
                    // set line to history
                    rl.line->len = rl.orig_line_len;
                    vstr_add_str(rl.line, MP_STATE_PORT(readline_hist)[rl.hist_cur]);
                    // set redraw parameters
                    redraw_step_back = rl.cursor_pos - rl.orig_line_len;
                    redraw_from_cursor = true;
                    redraw_step_forward = rl.line->len - rl.orig_line_len;
                }
            } else if (c == 'B') {
#if MICROPY_REPL_EMACS_KEYS
down_arrow_key:
#endif
                // down arrow
                if (rl.hist_cur >= 0) {
                    // decrease hist num
                    rl.hist_cur -= 1;
                    // set line to history
                    vstr_cut_tail_bytes(rl.line, rl.line->len - rl.orig_line_len);
                    if (rl.hist_cur >= 0) {
                        vstr_add_str(rl.line, MP_STATE_PORT(readline_hist)[rl.hist_cur]);
                    }
                    // set redraw parameters
                    redraw_step_back = rl.cursor_pos - rl.orig_line_len;
                    redraw_from_cursor = true;
                    redraw_step_forward = rl.line->len - rl.orig_line_len;
                }
            } else if (c == 'C') {
#if MICROPY_REPL_EMACS_KEYS
right_arrow_key:
#endif
                // right arrow
                if (rl.cursor_pos < rl.line->len) {
                    redraw_step_forward = 1;
                }
            } else if (c == 'D') {
#if MICROPY_REPL_EMACS_KEYS
left_arrow_key:
#endif
                // left arrow
                if (rl.cursor_pos > rl.orig_line_len) {
                    redraw_step_back = 1;
                }
            } else if (c == 'H') {
                // home
                goto home_key;
            } else if (c == 'F') {
                // end
                goto end_key;
            } else {
                DEBUG_printf("(ESC [ %d)", c);
            }
        }
    } else if (rl.escape_seq == ESEQ_ESC_BRACKET_DIGIT) {
        if (c == '~') {
            if (rl.escape_seq_buf[0] == '1' || rl.escape_seq_buf[0] == '7') {
home_key:
                redraw_step_back = rl.cursor_pos - rl.orig_line_len;
            } else if (rl.escape_seq_buf[0] == '4' || rl.escape_seq_buf[0] == '8') {
end_key:
                redraw_step_forward = rl.line->len - rl.cursor_pos;
            } else if (rl.escape_seq_buf[0] == '3') {
                // delete
#if MICROPY_REPL_EMACS_KEYS
delete_key:
#endif
                if (rl.cursor_pos < rl.line->len) {
                    vstr_cut_out_bytes(rl.line, rl.cursor_pos, 1);
                    redraw_from_cursor = true;
                }
            } else {
                DEBUG_printf("(ESC [ %c %d)", rl.escape_seq_buf[0], c);
            }
        } else {
            DEBUG_printf("(ESC [ %c %d)", rl.escape_seq_buf[0], c);
        }
        rl.escape_seq = ESEQ_NONE;
    } else if (rl.escape_seq == ESEQ_ESC_O) {
        switch (c) {
            case 'H':
                goto home_key;
            case 'F':
                goto end_key;
            default:
                DEBUG_printf("(ESC O %d)", c);
                rl.escape_seq = ESEQ_NONE;
        }
    } else {
        rl.escape_seq = ESEQ_NONE;
    }

    // redraw command prompt, efficiently
    if (redraw_step_back > 0) {
        mp_hal_move_cursor_back(redraw_step_back);
        rl.cursor_pos -= redraw_step_back;
    }
    if (redraw_from_cursor) {
        if (rl.line->len < last_line_len) {
            // erase old chars
            mp_hal_erase_line_from_cursor(last_line_len - rl.cursor_pos);
        }
        // draw new chars
        mp_hal_stdout_tx_strn(rl.line->buf + rl.cursor_pos, rl.line->len - rl.cursor_pos);
        // move cursor forward if needed (already moved forward by length of line, so move it back)
        mp_hal_move_cursor_back(rl.line->len - (rl.cursor_pos + redraw_step_forward));
        rl.cursor_pos += redraw_step_forward;
    } else if (redraw_step_forward > 0) {
        // draw over old chars to move cursor forwards
        mp_hal_stdout_tx_strn(rl.line->buf + rl.cursor_pos, redraw_step_forward);
        rl.cursor_pos += redraw_step_forward;
    }

    return -1;
}