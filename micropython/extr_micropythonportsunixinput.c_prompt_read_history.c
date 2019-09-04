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

void prompt_read_history(void) {
#if MICROPY_USE_READLINE_HISTORY
    #if MICROPY_USE_READLINE == 1
    readline_init0(); // will clear history pointers
    char *home = getenv("HOME");
    if (home != NULL) {
        vstr_t vstr;
        vstr_init(&vstr, 50);
        vstr_printf(&vstr, "%s/.micropython.history", home);
        int fd = open(vstr_null_terminated_str(&vstr), O_RDONLY);
        if (fd != -1) {
            vstr_reset(&vstr);
            for (;;) {
                char c;
                int sz = read(fd, &c, 1);
                if (sz < 0) {
                    break;
                }
                if (sz == 0 || c == '\n') {
                    readline_push_history(vstr_null_terminated_str(&vstr));
                    if (sz == 0) {
                        break;
                    }
                    vstr_reset(&vstr);
                } else {
                    vstr_add_byte(&vstr, c);
                }
            }
            close(fd);
        }
        vstr_clear(&vstr);
    }
    #endif
#endif
}