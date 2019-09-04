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
typedef  int /*<<< orphan*/  vstr_t ;

/* Variables and functions */
 int mp_hal_stdin_rx_chr () ; 
 int /*<<< orphan*/  readline_init (int /*<<< orphan*/ *,char const*) ; 
 int readline_process_char (int) ; 

int readline(vstr_t *line, const char *prompt) {
    readline_init(line, prompt);
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        int r = readline_process_char(c);
        if (r >= 0) {
            return r;
        }
    }
}